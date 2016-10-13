# VOIP Producer


VOIP Producer is an 8 Line VOIP softphone. The purpose is to be able to manage calls for a call in talk show quickly and efficiently.

When completed, a host will be able to manage caller info as well as interchange which call is on the air, on hold, or just plain rude and should be dropped. With support for multiple audio sources, Producer will allow a caller to hear the host if the call is designated as on-air, or hear the audio from the program on hold audio source.

I was motivated to create this project because I needed a *free* solution to handling callers without having to worry about thousands of dollars of hardware and software. This app is also portable so it can come with me whereever I choose to host my show.

### Libraries / APIs

VOIP Producer uses a two open source projects to work properly:

* [PJSIP] - Open source SIP library for applications. I use the pjsua2 C++ API
* [wxWidgets] - A cross-platform GUI and tools library for GTK, MS Windows, and MacOS.

### Development
When completed, I will provide the instructions on how to include both PJSIP and wxWidgets into your cloned Xcode project. The process is not straight forward as the linker flags and dynamic library details are very specific.
