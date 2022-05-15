# Disclaimer

**Since I have graduated, I am making all of my university related repositories public in the hope it might be useful to someone.**

**I do not condone plagarism, so please think twice before attempting a stunt like that.**

**There may be parts of these repositories where the Copyright or Intellectual Property is owned by others (including UNSW). I do not attempt to make any claim that they are my own. If there is a cause for concern, please reach out and I will do my best to rectify it.**

**Otherwise, please refer to the LICENSE file provided in this repository.**

# COMP1511
My C Source Code for UNSW COMP1511 2017

Overall in this course I achieved a **High Distinction** with a final mark of **90%**.

[COMP1511 Semester 1 2017 Homepage](https://webcms3.cse.unsw.edu.au/COMP1511/17s1/)

## Lab Exercises
All folders in this git repository in with a name in the form lab<number> are my solutions to the lab exercises 
for a given week in COMP1511 Semester 1 2017. There have been challenge exercises also set for most weeks.
Whereby having a significant attempt at the challenge could get you an **A+** mark over a **A** mark.

**Note that for every week, I have achieved at least an **A** mark, so have attempted all the required exercises and gotten
them correct.**
01. [Lab 01 Exercises Spec](https://cgi.cse.unsw.edu.au/~cs1511cgi/17s1/lab/01/questions) (Mark: **A**)
02. [Lab 02 Exercises Spec](https://cgi.cse.unsw.edu.au/~cs1511cgi/17s1/lab/02/questions) (Mark: **A+**)
03. [Lab 03 Exercises Spec](https://cgi.cse.unsw.edu.au/~cs1511cgi/17s1/lab/03/questions) (Mark: **A+**)
04. [Lab 04 Exercises Spec](https://cgi.cse.unsw.edu.au/~cs1511cgi/17s1/lab/04/questions) (Mark: **A+**)
05. [Lab 05 Exercises Spec](https://cgi.cse.unsw.edu.au/~cs1511cgi/17s1/lab/05/questions) (Mark: **A+**)
06. [Lab 06 Exercises Spec](https://cgi.cse.unsw.edu.au/~cs1511cgi/17s1/lab/06/questions) (Mark: **A**)
07. [Lab 07 Exercises Spec](https://cgi.cse.unsw.edu.au/~cs1511cgi/17s1/lab/07/questions) (Mark: **A**)
08. [Lab 08 Exercises Spec](https://cgi.cse.unsw.edu.au/~cs1511cgi/17s1/lab/08/questions) (Mark: **A**)
09. [Lab 09 Exercises Spec](https://cgi.cse.unsw.edu.au/~cs1511cgi/17s1/lab/09/questions) (Mark: **A+**)
10. [Lab 10 Exercises Spec](https://cgi.cse.unsw.edu.au/~cs1511cgi/17s1/lab/10/questions) (Mark: **A**)
11. [Lab 11 Exercises Spec](https://cgi.cse.unsw.edu.au/~cs1511cgi/17s1/lab/11/questions) (Mark: **A**)
12. [Lab 12 Exercises Spec](https://cgi.cse.unsw.edu.au/~cs1511cgi/17s1/lab/12/questions) (Mark: **A**)
13. [Lab 13 Exercises Spec](https://cgi.cse.unsw.edu.au/~cs1511cgi/17s1/lab/13/questions) (Not Marked: but my solutions passed all tests, so **A**)

**NOTE:** Sample Solutions for each week's lab exercises can be found by clicking on the *"Exercises"* dropdown 
menu at the top of the page, and selecting *"Sample Solutions"*.

## Assignments
There are two assignments in this course.
My solutions to these assignments can be found in the folders **assignment1** and **assignment2**.
1. [Assignment 1 **CAPTCHA Cracking** Spec](https://cgi.cse.unsw.edu.au/~cs1511/17s1/assignments/captcha/index.html)
2. [Assignment 2 **Trader Bot** Spec](https://cgi.cse.unsw.edu.au/~cs1511/17s1/assignments/trader_bot/index.html)

### Assignment 1
**NOTE:** That for assignment 1, I first attempted to crack the digits by using a [Feedforward Back-propagating Neural 
Network](https://en.wikipedia.org/wiki/Feedforward_neural_network), which didn't seem to work for me at all, so I decided 
to revert back to manually identifying and quantifying features in the digits and identifying the digits that way.

You will notice that my assignment 1 is written in Python, I did this so I could prototype faster and quickly create an algorithm
to extract features from the digits and make an educated guess as to what the value of the digit it was trying to crack was.
Once I had my Python algorithm at what I thought was an acceptable accuracy, I started to translate the whole Python program to C.
This included writing helper functions that are built into Python, but not C, and also adjusting function arguments to work with C.

**ALSO NOTE:** That after translating my Python algorithm to C, I later went ahead and improved on the algorithm, so know that it is
not a one-to-one translation. *They are not the same program!!!*

#### Assignment 1 Sample CAPTCHA images (PBMs)
- [1000 Example Digits](https://cgi.cse.unsw.edu.au/~cs1511/17s1/assignments/captcha/digit.html)
	- [Download](https://cgi.cse.unsw.edu.au/~cs1511/17s1/assignments/captcha/digit.zip)
- [1000 Example CAPTCHAs](https://cgi.cse.unsw.edu.au/~cs1511/17s1/assignments/captcha/captcha.html)
	- [Download](https://cgi.cse.unsw.edu.au/~cs1511/17s1/assignments/captcha/captcha.zip)
- [1000 Example Challenge CAPTCHAs](https://cgi.cse.unsw.edu.au/~cs1511/17s1/assignments/captcha/captcha_challenge.html)
	- [Download](https://cgi.cse.unsw.edu.au/~cs1511/17s1/assignments/captcha/captcha_challenge.zip)
	- **NOTE:** I did not attempt this due to time restrictions after wasting so much time on the idea of Neural Networks.

#### Performance Marks
For this assignment, all programs were auto-marked by testing the program against an unspecified set of unseen CAPTCHA images.

My program achieved the following results:
- **275 of 300**(*91.67% accuracy*) single digit CAPTCHAs recognized
- **744 of 800**(*93% accuracy*) digits in CAPTCHAs recognized (i.e. Tested with 200, 4 digit CAPTCHAS, so 800 digits total, got 744 correct)
- **27 of 400**(*6.75% accuracy*) digits in challenge CAPTCHAs recognised *(This, I thought was facinating, since I did not write any code to 
specifically crack the challenge CAPTCHAs.*

**NOTE:** The accuracy from the auto-marking is remarkable close to the accuracy I was getting with the sample data/images provided.
This is most likely because the same algorithm was used to generate the images.

This resulted in a mark of **68.4/80**(*85.5%*) for the program aspect of the assignment.

#### Final Marks
I received **15/15** and **5/5** for my code style and blog respectively, which resulted in a final mark of **88.4/100**.

### Assignment 2
Much like Assignment 1, all programs were auto-marked. In this case, all bots were run in a specified set of worlds as the only bot, and there were also multi-bot tournaments. The percentage profit was gauged by taking the bot that performed the best and making your profit a percentage of the max made. So 50% would mean your bot made half as much profit as the best bot. My bot at its best placed **37th** from some 630+ other bots in the multi-bot tournament.

#### Performance Marks
My bot averaged these results:
- Average single-bot profit (118 worlds): **58.3%**
- Average multi-bot profit: **45.1%**

My assignment received a final performance mark of **71.5/80**(*89.375%*).

#### Final Marks
I received **15/15** and **5/5** for my code style and blog respectively, which resulted in a final mark of **91.5/100**.
