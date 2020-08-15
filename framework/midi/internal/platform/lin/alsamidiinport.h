//=============================================================================
//  MuseScore
//  Music Composition & Notation
//
//  Copyright (C) 2020 MuseScore BVBA and others
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License version 2.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//=============================================================================
#ifndef MU_MIDI_ALSAMIDIINPORT_H
#define MU_MIDI_ALSAMIDIINPORT_H

#include <thread>

#include "imidiinport.h"

namespace mu {
namespace midi {
class AlsaMidiInPort : public IMidiInPort
{
public:
    AlsaMidiInPort();
    ~AlsaMidiInPort();

    std::vector<MidiDevice> devices() const override;

    Ret connect(const MidiDeviceID& deviceID) override;
    void disconnect() override;
    bool isConnected() const override;
    MidiDeviceID deviceID() const override;

    void run() override;
    void stop() override;
    bool isRunning() const override;
    async::Channel<std::pair<tick_t, Event> > eventReceived() const override;

private:

    static void process(AlsaMidiInPort* self);
    void doProcess();

    struct Alsa;
    Alsa* m_alsa = nullptr;
    MidiDeviceID m_connectedDeviceID;
    std::shared_ptr<std::thread> m_thread;
    std::atomic<bool> m_running{ false };
    async::Channel<std::pair<tick_t, Event> > m_eventReceived;
};
}
}

#endif // MU_MIDI_ALSAMIDIINPORT_H
