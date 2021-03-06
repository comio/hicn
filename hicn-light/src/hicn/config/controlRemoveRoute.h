/*
 * Copyright (c) 2017-2019 Cisco and/or its affiliates.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file control_RemoveRoute.h
 * @brief Remove a route from the FIB
 *
 * Implements the "remove route" and "help remove route" nodes of the command
 * tree
 *
 */

#ifndef Control_RemoveRoute_h
#define Control_RemoveRoute_h

#include <hicn/config/controlState.h>
CommandOps *controlRemoveRoute_Create(ControlState *state);
CommandOps *controlRemoveRoute_HelpCreate(ControlState *state);
#endif  // Control_RemoveRoute_h
