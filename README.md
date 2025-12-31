## LoadLib
<img width="518" height="162" alt="LoadLib" src="https://github.com/user-attachments/assets/f590dd9c-35d7-4e1b-9867-0f8c2e345eb9" /><br>
A simple, effective tool to use when needing to inject a DLL at runtime

# What does it do?
LoadLib uses the LoadLibraryW function on Windows to load a selected DLL at runtime. Though noisy in most anticheat environments, it makes for a useful tool when testing internal hacks on programs with minimal/no anticheat.

# How do I create an EXE from this source code?
Find a compiler (I used MSVC) and compile to x86 (32-bit), as Release version (unless you want to modify and debug this code under Debug, instead). 

LoadLib also comes with simple UI elements, those being a title menu and a pointer denoting where your typing area is.

## Enjoy!
This was very fun to make, aside from the 1 time I lost all the source code to handling.cpp, and had to rewrite it through context clues and old bits of the file I had saved and scattered around my computer and various websites.
