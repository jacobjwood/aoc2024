# Advent of Code 2024

Now that I'm a "proper" software engineer (still ML focused), it's time to bite the bullet and learn some C++. I'll try and add summaries as I go along, as well as lessons learned.

## Setup

- Libcurl required inside of lib folder.
- clang-format and cmake installed.

## Lessons Learned

### Day 1

- Templates are useful
- Methods are unintuitively named coming from Python
- Back inserter is a thing

### Day 2

- Nothing learned here, just disappointed in myself. After all the LC this year and I still screw up basic edge cases. Nested conditionals not pretty either.

### Day 3

- Thank god regex is in the standard library as of C++11
- Iterators can be more efficient doing left increment instead of right increment, because i++ reconstructs a temporary variable. For primitives this isn't a problem, but for more complex iterators it can lead to slowdown.

### Day 4

- Tuples/pairs are not hashable - need to declare a function.
- Vector of tuples don't have a default constructor so are more verbose to create


### Day 5

- Hacky. Should be more efficient than this but brute force still works.

### Day 6

- Brute force ftw.

### Day 7

Never assume input can be parsed into hashmap. Ended up with hash collision that I missed for hours wondering why things weren't working. Iterative solution with bitmask was interesting but would've been bad for part 2.


### Day 8

Good food.

### Day 9

I hate my life. Why do I torture myself like this.

### Day 10

Redemption.

### Day 11

Thought was DP. Then used hashmap. Was not DP.

### Day 12

Interesting. Leetcode prepared me well for this.

### Day 13

Maths degree going in bin. Also precision go brrr.

### Day 14

Mod doesn't work properly in C++. Fun printing stuff.

### Day 15

NEED TO STOP TRYING TO DO TWO THINGS IN THE SAME LINE OF CODE. Mutation nightmare, state passing nightmare.

### Day 16

Who needs time complexity when you've got C++.
