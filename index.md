# Capstone Jacob Mousseau

For the capstone course, we have to show our competency with certain categories of work and how we can meet those goals, first and foremost, here is the code review video, Below it is a link to the script I used to guide myself, but it should not be 1 to 1 in this case. 

<h2>CODE REVIEW VIDEO IMAGE</h2>

<iframe width="560" height="315" src="https://www.youtube.com/embed/7VPagv84TxQ" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

[Script](Code Review Script.rtf)

<h1>CATEGORY 1:</h1>
<h2>Enhancement: Software Design and Engineering</h2>
<h3>File Used: Encryption.cpp</h3>
[Narrative](Category 1 Narrative.rtf)

The full narrative is available at the link above, but, to give a run down, this file is from my 405 course. And the goal of it originally was to make sure I understood how to encrypt and decrypt files using code, by completing the TODO sections of the code. To enhance it, I modified the code TODO's to make them a bit more useful, before also translating it from C++ to Python, which also involved splitting the code into two files for better legibility.

A design flaw that is still present after these enhancements though, is the fact that the key is pretty obvious within the code itself, altough this is for testing our knowledge, it would be better for the key to be hidden more so, maybe within a separated file of it's own, that gets plugged in. While this allows us to use anything as our encryption key, if we were to use this particular code in a real world environment, it would be pointless to use because it gives us the key, it encrypts the input file, but then also decrypts it by itself. It would make more sense to have encryption and decryption as separated files. So my next goal if I continued to work on it would be to separate the functions into two files. Below is the code of the python files, the original CPP code can be found [here.](Encryption.cpp)

Encryption.py
![Encryption PY](IMG Encryption PY.png)
Globals.py
![Globals PY](IMG Globals PY.png)

