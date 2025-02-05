# Digital Timer
 
Include your responses to the bold questions below. Include snippets of code that explain what you did. Deliverables are due next Tuesday. Post your lab reports as README.md pages on your GitHub, and post a link to that on your main class hub page.

## Part A. Solder your LCD panel

![soldered](https://github.com/AlanaCrognale/IDD-Fa19-Lab2/blob/master/soldered.png)

## Part B. Writing to the LCD
 
**a. What voltage level do you need to power your display?**

5V

**b. What voltage level do you need to power the display backlight?**

3.3V
   
**c. What was one mistake you made when wiring up the display? How did you fix it?**

I found that my wires sometimes kept coming out of the breadboard if I wasn't careful and bumped into something else - have extra caution when handling a breadboard with so many wires and make sure that wires are securely in place.

**d. What line of code do you need to change to make it flash your name instead of "Hello World"?**

lcd.print("hello, world!"); to lcd.print("Alana!");
 
**e. Include a copy of your Lowly Multimeter code in your lab write-up.**

![lowlymultimeter](https://github.com/AlanaCrognale/IDD-Fa19-Lab2/blob/master/Lowly_Multimeter.ino)

## Part C. Using a time-based digital sensor

**Upload a video of your working rotary encoder here.**

![lowlymultimeter](https://github.com/AlanaCrognale/IDD-Fa19-Lab2/blob/master/Rotary%20Encoder.mov)

## Part D. Make your Arduino sing!

**a. How would you change the code to make the song play twice as fast?**

Change 1000 to 500 in line "int noteDuration = 1000/noteDurations[thisNote];", halving each note duration
 
**b. What song is playing?**

Star Wars

## Part E. Make your own timer

**a. Make a short video showing how your timer works, and what happens when time is up!**

![timer countdown](https://github.com/AlanaCrognale/IDD-Fa19-Lab2/blob/master/Timer_Countdown.ino) along with ![pitches.h](https://github.com/AlanaCrognale/IDD-Fa19-Lab2/blob/master/pitches.h)

'Simon Says' esque game: First, the player turns the knob to represent how many light patterns to memorize (and how much time they will have to memorize).  Note that I have this set to max out at 100 such that if the knob is turned to any value greater than 100, the timer will reset back to 100.  Then, the player presses the yellow LED button to set the time and to begin the game.  The randomized pattern is then displayed, and once this is complete, the countdown begins.  At any point during this countdown, once the player feels like they have successfully memorized the pattern and is ready to re-enter, they can press the yellow LED button to signal that they are ready to enter the pattern, and then they will press each button in order coresponding to the pattern just displayed.  If the player never presses the yellow LED button to signal that they have the pattern memorized and are ready to play, the player loses the game once the timer reaches 0, and a 'losing' message is displayed on the screen along with a negative sounding descending C minor chord playing out of the speakers (![no time](https://github.com/AlanaCrognale/IDD-Fa19-Lab2/blob/master/no%20time.mov)).  If the player incorrectly enters the pattern, they lose the game, and a 'losing' message is displayed on the screen along with the same descending C minor chord (![wrong pattern](https://github.com/AlanaCrognale/IDD-Fa19-Lab2/blob/master/wrong%20pattern.mov)).  If the player correctly enters the pattern, they win the game, and a 'winning' message is displayed along with a positive sounding ascending C major chord (![won](https://github.com/AlanaCrognale/IDD-Fa19-Lab2/blob/master/won.mov)).

**b. Post a link to the completed lab report your class hub GitHub repo.**
