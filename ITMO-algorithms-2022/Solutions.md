# A. Агроном-любитель

## Problem

In the array of N numbers, find the longest sequence which does not have three consecutive numbers of the same value and print the indices of first and last number.

## Example

**IN**
```
6
5 6 6 6 23 9
```

**OUT**
```
3 6
```

## Solution

The blocks of three or more repeating numbers break the input sequence into zones. For example:

```

 Zone #n-1 |               |    Zone #n    |               | Zone #n+1
... 7 1 3 4 2 2 2 ... 2 2 2 8 9 9 ... 4 2 3 1 1 1 ... 1 1 1 2 5 9 0 ... 

```

Since there are no groups of three or more repeating numbers in each zone, we can form a sequence out of all numbers in this zone. On top of that, we can add two closest numbers from each groups that separate those zones into the sequence, this will still be valid:

```

 Zone #n-1 |               |    Zone #n    |               | Zone #n+1
... 7 1 3 4 2 2 2 ... 2 2 2 8 9 9 ... 4 2 3 1 1 1 ... 1 1 1 2 5 9 0 ... 
 Sequence #n-1 |       |      Sequence #n      |       | Sequence #n+1

```

Also sequence of two repeated numbers is still a valid sequence, so if no better solution is avaliable, it could be the largest one.

Solution is following: iterate through array while keeping track of current sequence's start point. Break sequence if current number is equal to both previous and next number. New sequence starts from the second-to-last of the group of consecutive equal numbers. Keep track of unbroken sequence of maximum length, print it out at the end.

**Time complexity** Algorithm iterates through each number when searching for sequences - O(N)

**Memory complexity** O(1), no need to s

**Contest result** - 33ms, 380.00Kb

# B. Зоопарк Глеба

## Problem

Several animals (represented as lowercase English letters) are spread on the circumference. Each animal has a cage (represented as respective uppercase English letters), which are also spread on circumference. Animal can be connected directly with its cage via a chord, but chords for two different animals (different letters) cannot intersect. Find out if this is possible.

Input is a string of letters - this is how animals and cages are located on circumference, one after the other. The last element in the string precedes the first one. 

If connection is possible, for each cage also print the index of animal inside of it.

## Example

**IN**
```
ABba
```

**OUT**
```
Possible
2 1
```

Note that final indices of animals are calculated without cages, so 'b' here is the first element, `'a'` is the second one.

**IN**
```
ABab
```

**OUT**
```
Impossible
```

## Solution

1. How to find out that two pairs in input sequence intersect with each other when we put them on circumference?

A chord cuts circle into two pieces - input looks like this:

```
...#1... A ...#2... a ...#1...
```

Obviously, all elements on the left from `'A'` are located in the same piece as the ones on the right from `'a'`, since last element precedes the first on circumference. We can say that all elements between `'A'` and `'a'` (#2) are located "inside" of the chord, while other elements (#1) are outside.

For a new chord `'Bb'` to not intersect `'Aa'`, it should either be fully inside, or fully outside of `'Aa'`.

2. Even though chords of same animals can intersect with each other, it is better not to intersect them.

Consider following example:

```
...#1... A ...#2... A ...#3... a ...#4... a ...#1...
```

Let's assume there are only two `'Aa'` pairs. Then we have two cases, let's see how many choices of connecting surrounding sequences we have:

* `'Aa'` pairs intersect (first `'A'` connects with first `'a'`, second `'A'` connects with second `'a'`) - two chords break the circle into four sectors, sequences representing these sectors cannot be cross-connected.

* `'Aa'` pairs do not intersect (first `'A'` connects with second `'a'`, second `'A'` connects with first `'a'`) - we can connect #2 and #4 now! #1 and #3 are still kinda isolated, but that is OK.

As you can see, if we choose not to intersect, we have more options of connecting chords. So following solution makes sure that no two chords intersect with each other.

3. If the solution is possible, there exists at least one chord which does not have any elements inside of it (letters on the line are consecutive)

Proof: choose any chord - if it has a chord inside of it, choose that chord and repeat. Each step will create chords of smaller size - at one point, we will have a chord without chords inside. If there are still elements inside, then solution is not possible (these elements should have a pair, but their pairs are outside of the chord => intersection!). If no elements are inside, chord is found.

4. Creating chords

For each element, let's track its pair which it uses to form a chord. Now we iterate and check if an element is the right element of the chord. On iteration i, initialize j with i-1: we will try to make a pair j <-> i. Now we have possible situations:

* If #j is already paired with some number #k, we will try to put chord j <-> k inside of whatever chord #i will create, so assign j = k-1 and try to make a pair with new #j. Note that #k-1 might be paired with some other element, so this process can continue multiple times.
* If #j is not paired, but #j is not the pair for #i, #i cannot be the right element of the chord => continue.
* If #j is not paired and #j is the pair for #i, create a chord j <-> i.

At the end, check that all elements are paired with each other - then we found our solution! In that case, print whatever indices you need.

**Time complexity**: Even though we do some backtracking at each iteration, each chord is visited exactly once: after we found #j to pair with #i, we put the chords that we visited inside of a newly created j <-> i. The chords that are inside will be skipped on next iterations. So, O(N).

**Memory complexity**: O(N) to store all elements and their pairs.

**Contest result**: 8ms, 1020.00Kb  

# C. Конфигурационный файл

## Problem

The file consists of four possible line types:
* Opening curly bracket `'{'` - start of the block
* Closing curly bracket `'}'` - end of the block
* Line `<variable>=<number>` - assign `<number>` to `<variable>`
* Line `<variable1>=<variable2>` - assign whatever value `<variable2>` has to `<variable1>`

Each assignment is valid only until the end of the block where assignment happened. `<variable1>=<variable2>` line assigns 0 if `variable2` is not yet assigned at all.

For each line `<variable1>=<variable2>`, print the value that was effectively assigned to `variable1`.

## Example

**IN**

```
a=b
b=123
var=b
b=-34
{
c=b
b=1000000000
d=b
{
a=b
e=var
}
}
b=b
```

**OUT**

```
0
123
-34
1000000000
1000000000
123
-34
```

## Solution

Note that we need to keep information about multiple assignments to the same variable. Example:

```
a=1
{
a=2
{
a=3
{
a=4
b=a // 4
}
b=a // 3
}
b=a // 2
}
b=a // 1
```

As you can see, 8th line should know about 7th and at the same time 10th line should know about 5th, so we cannot simply overwrite variable with new value if we do not want to perform some weird backtracking.

Solution - push all assignments to each variable into some structures. Assignments contain information about new value and the depth on which they happened. When reading from variable, read the value from last assignment. When we exit some block, remove all assignments that happened on the current block (they should be on top of whatever structures we use to push assignments). Variable is initialized with value 0.

Quick optimization - when pushing assignment, if assignment already happened on current block, just rewrite it, do not push. This way, each block has only one assignment written into the structure, so it is easier to clean them up.

So, here are the operations that our structure should support:
1. Creating new variable (structure is initialized with single value - 0)
2. Lookup of the variable (accessing structure where we store assignments)
3. Write of new assignment
4. Read of last assignment
5. Clearing top elements of some variable structures (if top assignment happened at current block)

This looks like a work for hash-table based associative array! Key would be a string (variable name, to be exact), value - stack of assignments and the depths when they happened:

1. Creating new variable: associative array insert + stack push: constant time
2. Lookup of the variable: associative array lookup: constant time
3. Write of new assignment: stack push or (peek + rewrite): constant time
4. Read of last assignment: stack peek: constant time
5. Clearing top elements of some variable structures: iterating over associative array + stack peek + stack pop: **O(number_of_variables)** (sloooow)

There can be blocks where no assignments happen, and they still have to iterate over all variables! Using this structure, we can only reach O(N^2) complexity for N = line count.

How can we optimize cleanup? I have come up with two ways.

First idea is to keep track of variables that got changed in all block depths up to and including current one, independent of each other. On entering the block, new structure to track is allocated. On each assignment, variable name is added into the structure. On exiting the block, we iterate over the structure and clear top elements of all variable stacks that are referenced by this, then structure is deallocated.

Again, operations:

1. Allocate new structure
2. Check if variable exists
3. Insert variable
4. Iterate and clear top elements
5. Deallocate structure

Variable names could be stored in hash-table based set, sets themselves are stored in stack.

1. Allocate new structure: stack push + set initialization: constant time
2. Check if variable exists: set lookup: constant time
3. Insert variable: set insert: constant time
4. Iterate and clear top elements: iterating over set + associative array lookup (see main structure) + stack pop: **O(number_of_changes_in_block)**
5. Deallocate structure: stack pop: constant time

Much better! Clearing operations clear each assignment exactly once, so O(N) for those operations overall.

Second idea is to clear assignments from finished blocks lazily. That means, no clears on block exits will be performed, instead each read/write will try to remove outdated values from assignments stack before actually performing reads/writes.

How can we understand that assignment is outdated? Assignments now should store not only new value and block depth, but also the line number at which the current block started. Also there should be a vector of line numbers at which all current blocks have started. Current line number is pushed at block enter, popped at block exit.

Assignment is outdated if one of two is true:
* It happened at the deeper block level than the current one
* Current block is not a part of the block where it happened - the line numbers of block starts for the same depths differ

No more cleaning up at the block exit, so no O(number_of_variables). Read/write of assignments become slower though, because they do cleanups of outdated assignments. The complexity is **O(number_of_variable_assignments)**, but each assignment is handled only once => O(N) time complexity once again. Also note that supporting data structure takes much less space in second idea (stack of integers instead of stack of hash sets), which is also nice.

**Time complexity**: O(N) for number of lines, see above

**Memory complexity**: O(N) for number of lines, worst-case is the need to store all assignments at the same time

**Contest result**: 64ms, 9.06Mb

# D. Профессор Хаос

## Problem

Professor has some amount of bacteria in container at day 0 (A). Everyday he performs following actions:

* Takes bacteria into incubator where they are reproducing. Each bacterium splits into B bacteria;
* Takes out C bacteria (or all of them if bacteria count is less than C), experiments with them and throws them away;
* Puts bacteria back into container (only D bacteria can be put in container).

Input consists of five numbers: `A B C D N`. Return bacteria count at the end of N-th day.

Restrictions:
```
1 <= A <= D
B >= 1
C >= 0
D >= 1
```

## Example

**IN**
```
1 3 1 5 2
```

**OUT**
```
5
```

## Solution

We can simply deduct a recurrency formula (`T_N` - bacteria count at the end of day N):
```
T_N = max(min(B * T_(N-1) - C, D), 0)
T_0 = A

Opening min/max functions, T_N is either:
#1. 0 if B * T_(N-1) - C < 0
#2. D if B * T_(N-1) - C > D
#3. B * T_(N-1) - C otherwise
```

1. If `T_1 = A`, then for each N `T_N = T_(N-1)`.

Proof: `T_1` cannot be neither `#1` nor `#2` (see above), since then `A` is either 0 or `D`, which is impossible. So `T_1 = B * A - C`, or `(B - 1)A = C`.
