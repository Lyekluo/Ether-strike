# Project 2: Becoming a Librarian

# Overview

In this project, we're going to use a real world library! Specifically, we'll learn to compile our code with the Simple and Fast Multimedia Library ([SFML](https://www.sfml-dev.org)). This library works with your operating system to display graphics and play audio. You could use this library to make a game, a video editor app, or even a music player.

Your work will come in two steps. First, you'll have to download the library and get it to work on your computer. Second, you'll read some documentation and have fun wielding the power of a publicly-available library.

| File | What it's for |
| --- | --- |
| `hello_sfml.cpp` | A tiny program for checking that Step 1 worked. |
| `starters/minigame/main.cpp` | Starter 1: move a shape with the keyboard. |
| `starters/art/main.cpp` | Starter 2: a grid of colorful shapes. |
| `starters/drawing/main.cpp` | Starter 3: stamp shapes with mouse clicks. |
| `starters/animation/main.cpp` | Starter 4: a bouncing ball. |
| `starters/soundboard/main.cpp` | Starter 5: play notes with the keyboard. |

# Step 1: Loading the library.

For Step 1, you can use LLM chats as much as you want (ask it anything you want and use its response however you want), but please do not use agentic harnesses to do this for you. You are **expected to move files, modify configurations, and run commands yourself**, even if an LLM is instructing you.

> [!WARNING]
> Be wary of anything an LLM gives you. If it tells you to run commands or place files in certain places, don't default to trusting it. Make sure you understand the consequences of all of your actions.

Here's an example prompt you can use to ask your LLM for help:

> I'm trying to configure my C++ compiler to use the Simple and Fast Multimedia Library. Can you give me specific instructions to setup a hello world program using the SFML? Also, make sure to explain every step of the process and what the alternative options are.

Along the way, you're expected to:
- Install **SFML 3** (any 3.x version) on your computer. The starter code will *not* work with SFML 2, so check which version you're getting before you install it.
- Figure out the command to compile a program that uses SFML. Most setups look something like this, sometimes with extra flags:

    ```sh
    g++ -std=c++20 hello_sfml.cpp -o hello_sfml -lsfml-graphics -lsfml-window -lsfml-system
    ```
- Compile and run `hello_sfml.cpp`. You're done with Step 1 when a window opens with a **green circle** in it, and your terminal prints `Hello from SFML 3.x.x!`.
- Be able to explain, in your own words:
  - where the SFML header files (`.hpp`) and library files (`.a`, `.so`, `.dylib`, `.lib`, or `.dll`) ended up on your computer, and
  - what the `-I`, `-L`, and `-l` compiler flags do (even if your final command doesn't need all of them).

<details>
<summary><b>Tips</b> (click to expand)</summary>

The official [SFML Getting Started tutorials](https://www.sfml-dev.org/tutorials/3.0/#getting-started) are a good place to cross-check what your LLM tells you.

Things to avoid:
- **Don't mix compilers.** SFML must be built by the same compiler (and the same version of it) that you use to compile your program. If you have more than one compiler installed, make sure you know which one `g++` actually runs, and which one built the SFML you installed.
- **Don't mix SFML versions.** If you try more than one way of installing SFML, make sure your compiler isn't finding headers from one install and library files from another.

Things you could ask your LLM about:
- You may be able to use a **package manager** to get started quickly. Ask your LLM which package managers can install SFML on your operating system, and how to check which version of SFML a package would give you.
- If your compiler can't find SFML after installing it, ask your LLM how to find out *where* it was installed, and how to tell your compiler to look there.
- Building SFML **from source**, or using SFML's official **CMake template**, are alternatives if a package manager doesn't work out. Ask your LLM about the tradeoffs.

</details>

# Step 2: Using the library.

> [!IMPORTANT]
> **Different AI rules apply for Step 2.** You may use an LLM **only to help you find pages in the SFML documentation**. Do **not** ask it to write, complete, fix, or explain your code, and do not paste your code into it. Please turn off AI autocomplete (like GitHub Copilot) in your editor for this step. The goal is to practice reading real documentation, a skill you'll use for the rest of your programming life!
>
> An example of an OK prompt:
>
> > Which page of the SFML 3 documentation explains how to check if a key is being held down? Just give me the link.

## Part 2.1: Choose a starter

Pick **one** of the five starters below. Each is a complete, working, heavily-commented program in its own folder under `starters/`, and contains exactly **two TODOs** for you to complete. Compile it and run it before changing anything, so you know what it already does. For example:

```sh
cd starters/minigame
g++ -std=c++20 main.cpp -o main -lsfml-graphics -lsfml-window -lsfml-system
./main
```

(Use whatever extra flags you needed in Step 1. The soundboard also needs `-lsfml-audio`.)

If you'd rather build something else that's *equally small*, run your idea by the course staff first.

### 1. Mini game (`starters/minigame`)

A circle that moves left and right with the arrow keys.

- **TODO 1:** Make the circle also move up and down with the Up/Down arrow keys.
- **TODO 2:** Make the circle change color when you press Space.
- **Docs:** [Keyboard, mouse and joystick](https://www.sfml-dev.org/tutorials/3.0/window/inputs/) · [Events explained](https://www.sfml-dev.org/tutorials/3.0/window/events/)
- **Stretch ideas:** keep the circle from leaving the window; add a second shape to "collect."

### 2. Generative art (`starters/art`)

A grid of squares whose colors depend on their position.

- **TODO 1:** Give every square an outline.
- **TODO 2:** Rotate each square by an angle that depends on its column.
- **Docs:** [Shapes](https://www.sfml-dev.org/tutorials/3.0/graphics/shape/) · [Position, rotation, scale: transforming entities](https://www.sfml-dev.org/tutorials/3.0/graphics/transform/)
- **Stretch ideas:** use circles with a different number of points (triangles, hexagons); randomize the colors; change the pattern each time a key is pressed.

### 3. Drawing program (`starters/drawing`)

Left-click to stamp a circle where you clicked.

- **TODO 1:** Right-click to stamp a square where you clicked.
- **TODO 2:** Press C to clear the canvas.
- **Docs:** [Events explained](https://www.sfml-dev.org/tutorials/3.0/window/events/) · [`sf::RectangleShape` reference](https://www.sfml-dev.org/documentation/3.0.2/classsf_1_1RectangleShape.html) · [`std::vector::clear`](https://en.cppreference.com/cpp/container/vector/clear)
- **Stretch ideas:** press number keys to switch colors; draw continuously while the mouse button is held.

### 4. Animation (`starters/animation`)

A ball that bounces back and forth between the left and right walls.

- **TODO 1:** Make the ball also move vertically and bounce off the top and bottom walls.
- **TODO 2:** Make the square in the middle spin continuously.
- **Docs:** [Position, rotation, scale: transforming entities](https://www.sfml-dev.org/tutorials/3.0/graphics/transform/) · [Handling time](https://www.sfml-dev.org/tutorials/3.0/system/time/)
- **Stretch ideas:** change the ball's color every time it bounces; add more balls; make the square pulse in size.

### 5. Soundboard (`starters/soundboard`)

Press A, S, or D to play a note, and watch its pad light up.

- **TODO 1:** Add a fourth note that plays when you press F.
- **TODO 2:** Make the Up/Down arrow keys turn the volume of every note up/down.
- **Docs:** [Playing sounds and music](https://www.sfml-dev.org/tutorials/3.0/audio/sounds/) · [`sf::Sound` reference](https://www.sfml-dev.org/documentation/3.0.2/classsf_1_1Sound.html) (scroll down to see the functions it inherits from `sf::SoundSource`)
- **Stretch ideas:** change the pitch with the Left/Right arrow keys; load a `.wav` or `.ogg` file of your own; make a whole octave of keys.

## Part 2.2: Read the docs and extend your starter

Complete **both TODOs** in your starter. Each TODO comment includes a "Done when" line that tells you exactly what working looks like.

Then, make **at least one additional change of your choice** to personalize it, like a color, speed, size, sound, or control. It can be small! The stretch ideas above are great too, but not required.

When you're not sure how to do something, here's a process that works well:

1. **Find the relevant class.** Start from the tutorial linked for your starter, or search the [SFML API reference](https://www.sfml-dev.org/documentation/3.0.2/). The starter code already uses most of the classes you'll need, so look up the classes that appear near the TODO.
2. **Inspect the function signatures and examples.** What arguments does the function take, and of what types? Many class pages have an example at the bottom, under "Detailed Description."
3. **Try a small change.** Write the smallest piece of code that could work.
4. **Compile and test before continuing.** It's much easier to find a mistake in three new lines than in thirty.

# Submission

To submit the assignment, email the files below as attachments to `cs106l-aut2627-staff@lists.stanford.edu` from your Stanford email, with the email subject of `CS106L Project 2 Submission`. You may resubmit as many times as you'd like before the deadline.

Your submission should include:

1. **Your code:** your `main.cpp`, plus any other files needed to build and run it (for example, a sound file you added).
2. **Evidence it works:** a screenshot of your program running.
3. **A short `README.md`** answering these three questions in a few sentences each:

    ```md
    ## What I made
    Which starter you chose, and what your personal modification was.

    ## A documentation page I used
    A link to at least one SFML documentation page, and what you used it for.

    ## One thing I learned
    About SFML, libraries, compiling, or reading documentation.
    ```
