# EIKarnesisShift
 An UE5 project showcasing Enhanced Input in the context of Gameplay Abilities, with examples. Written fully in C++.
 
 ### Documentation
 https://github.com/tranek/GASDocumentation
 
 https://docs.unrealengine.com/4.26/en-US/InteractiveExperiences/Input/EnhancedInput/
 
 ### Concept
 As the traditional input system in UE becomes deprecated, it is advised to start using the new Enhanced Input. It lets the developer get more data from the user, handle complex inputs and implement runtime key remaps more easily. At the same time, GAS's abundance of boilerplate code can make the transision difficult. I created this project in hope you get to see and understand how to combine these two plugins together. At the same time, I recreated two Arkane Studios' DEATHLOOP abilities - Karnesis and Shift, to further demonstrate the implementation.

# If you have trouble with setting up GAS itself, please refer to my earlier repos and the documentation provided.

### Usage
Feel free to use this when setting up your project.
The main points of this projects are the AEIKSPlayable.h and .cpp files, in which EI setup, handles and mappings are set. When opening this project in Unreal Ediot take notice of the Inputs folder as it contains input actions (IA) and mapping context (MC). If you take code from this repo into your own project, please remember to enable the EI plugin and set default classes to enhanced ones in Project Settings->Input->Default Classes.

### Showcased DEATHLOOP abilities

# Karnesis (AbilityKarnesis.h)

https://github.com/Marcin-Galaska/EIKarnesisShift/assets/106023363/7e739783-7ebd-4d9a-9efc-7b94bf611878

https://github.com/Marcin-Galaska/EIKarnesisShift/assets/106023363/f1847a4d-f96b-4e7f-87ad-e7984af35303

# Shift (AbilityShift.h & ShiftIndicatorActor.h)

https://github.com/Marcin-Galaska/EIKarnesisShift/assets/106023363/e656a05d-8c0c-44ab-b8bd-c850b5e153d4

https://github.com/Marcin-Galaska/EIKarnesisShift/assets/106023363/9e0e8654-05ec-4e00-8187-5ae9f36f2337

Video quality reduced due to GitHub file size requirements. Better quality files available in repository.

Be sure to create abilities from your own, custom class and not from the default GameplayAbility class.

Have fun!

### License
BSD 2-Clause License

Copyright (c) 2023, Marcin Gałąska <br>
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS “AS IS” AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
