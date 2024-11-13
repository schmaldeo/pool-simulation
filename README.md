# Pool simulation

## About

This is my uni project that displays simulated path a cue ball would take on a flat pool table. 
You can test it yourself, either by building it from source yourself, or by downloading a  [pre-built release](https://github.com/schmaldeo/pool-simulation/releases/latest). 

## Problem

Let a 4x2 rectangle, which will represent a pool table. On this table, in any
place inside its edges we place a ball. Next, we shoot the ball in any given
direction. We’re interested in the path the ball takes.

We assume that the centre point of the table is the beginning (P (0, 0)) of the
cartesian coordinate system, that the shot strength is equal to the displacement
of the ball on an infinite table (without edges), e.g. a ball shot with strength
of 20 would travel 20 units. We also assume that the direction the ball would
go in will be determined by a vector (v[x, y]). Upon reaching the edge of the
table the ball bounces off it and loses 5% of its energy (e.g. if it was shot with
strength of 22 and hit an edge after 2, it would have only 19 and not 20 units of
energy left). We also assume that the table can be bigger than the base, given
a parameter to the program (m ≥ 1). Let m = 3, the table would be a 12x6
rectangle:

P = {(x, y) ∈ R2 : −6 ≤ x ≤ 6, −3 ≤ y ≤ 3}

To summarise, the task is to write a program which will take 6 arguments:
1. m ≥ 1 - table size multiplier
2. s > 0 - shot strength
3. x - x coordinate of ball’s initial placement
4. y - y coordinate of ball’s initial placement
5. wx - x coordinate of ball’s initial vector
6. wy - y coordinate of ball’s initial vector

The program must print a drawing of the path the ball will take in console, if
it travels from the initial point, with the given strength, initially in the direction
described by the given vector.

## Concept

You can read about the concept of this solution in [this PDF](https://github.com/schmaldeo/uni-project/blob/master/concept.pdf).

## Screenshots

![](https://i.imgur.com/DYPdT4V.png)
![](https://i.imgur.com/NZFBF7O.png)
![](https://i.imgur.com/fQPp3iv.png)

## Credits

Big credit goes to [@nothings](https://github.com/nothings), whose 
[dynamic array implementation](https://github.com/nothings/stb/blob/master/stb_ds.h) available in public domain I'm using.