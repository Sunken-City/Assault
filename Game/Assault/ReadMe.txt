       _       ______    ______        _   _____  _____  _____   _________
      / \    .' ____ \ .' ____ \      / \ |_   _||_   _||_   _| |  _   _  |
     / _ \   | (___ \_|| (___ \_|    / _ \  | |    | |    | |   |_/ | | \_|
    / ___ \   _.____`.  _.____`.    / ___ \ | '    ' |    | |   _   | |
  _/ /   \ \_| \____) || \____) | _/ /   \ \_\ \__/ /    _| |__/ | _| |_
 |____| |____|\______.' \______.'|____| |____|`.__.'    |________||_____|


================================================================================
Known Issues:
================================================================================

Using the alt key to break out of the window, or any other exploit that causes 
time to pass without being able to check for collisions, could result in an entity getting
out of the stage's bounds and creating a crash.

================================================================================
How to Use:
================================================================================

Xbox Controller Controls:

Left & Right Stick Up - Move tank forward
Left & Right Stick Down - Move tank backward
Left Stick Up, Right Stick Down - Rotate tank clockwise
Left Stick Down, Right Stick Up - Rotate tank counterclockwise

Keyboard Controls:

Esc - Quit the Program
G - Turn on debugging radius

================================================================================
Deep Learning:
================================================================================

During this milestone, I learned an extremely valuable lesson while dealing with
an unintentional global instantiation. I had been coding my texture class when
I ran into an odd issue: a static std::map was segfaulting whenever I attempted
to access it. After a lot of debugging and help, I learned that the problem was
in a completely different area, due to a constructor I had accidentally called
while instantiating a static parameter. Although this sounds like a one-off
lesson, I learned something much deeper: It's extremely easy to make assumptions
about code that don't necessarily hold to be true. I had implicitly assumed
that things would get initialized in the order that I imagined in my head, and
that the member variables would get initialized when creating the object, just
like how I would have wanted them to. This is a dangerous assumption, as the
C++ standard has many counterintuitive compilation and runtime decisions that
can cause you grief if you don't know about them. I'm going to try and become
more aware not only of my own implicit assumptions, but also attempt to gain
a better familiarity with the inner workings of the language to replace these
implicit assumptions with knowledge.
