// Copyright 2019 Google LLC & Bastiaan Konings
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// written by bastiaan konings schuiling 2008 - 2014
// this work is public domain. the code is undocumented, scruffy, untested, and should generally not be used for anything important.
// i do not offer support, so don't ask. to be used for inspiration :)

#ifndef _HPP_SYSTEMS_IFACE_TASK
#define _HPP_SYSTEMS_IFACE_TASK

#include "../types/thread.hpp"
#include "../types/command.hpp"
#include "../base/properties.hpp"
#include "../base/log.hpp"

namespace blunted {

  class ISystemTask : public Thread {

    public:
      ISystemTask() {
      }

      virtual ~ISystemTask() {}

      virtual void operator()() = 0;

      /// the actual per-frame system work
      virtual void GetPhase() = 0;
      virtual void ProcessPhase() = 0;
      virtual void PutPhase() = 0;
      void SetEnabled(bool enabled) {
        this->enabled = enabled;
      }

    protected:
      bool enabled = true;
  };


  // messages

  class ISystemTaskMessage : public Command {

    public:
      ISystemTaskMessage(const std::string &name, ISystemTask *task) : Command(name), task(task) {};
      ISystemTask *GetTask() {
        return task;
      }

    protected:
      ISystemTask *task;

  };

  class SystemTaskMessage_GetPhase : public ISystemTaskMessage {

    public:
      SystemTaskMessage_GetPhase(const std::string &name, ISystemTask *task) : ISystemTaskMessage(name, task) {};

    protected:
      virtual bool Execute(void *caller = NULL);

  };

  class SystemTaskMessage_ProcessPhase : public ISystemTaskMessage {

    public:
      SystemTaskMessage_ProcessPhase(const std::string &name, ISystemTask *task) : ISystemTaskMessage(name, task) {};

    protected:
      virtual bool Execute(void *caller = NULL);

  };

  class SystemTaskMessage_PutPhase : public ISystemTaskMessage {

    public:
      SystemTaskMessage_PutPhase(const std::string &name, ISystemTask *task) : ISystemTaskMessage(name, task) {};

    protected:
      virtual bool Execute(void *caller = NULL);

  };

}

#endif
