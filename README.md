# Hackathon-Squad
Your university is hosting its flagship annual hackathon, and you want to
assemble the ultimate dream team from a massive pool of freshman coders.
Each coder has a specific "Skill Rating" based on their coding speed and
problem-solving abilities, which contributes to the team's overall strength.

However, due to past rivalries and department drama, certain pairs of coders
refuse to work together. As the team captain, your task is to design an
algorithm to select a subset of coders that maximizes the total skill rating of
the squad without including any conflicting pairs.

Due to the massive scale of the student body, finding the absolute perfect
mathematical team might be computationally impossible. Your goal is to
apply optimization techniques to find a valid team with the highest possible
total skill rating within the time limit.
Goals
Total Score: Sum of the skill ratings of all selected coders.

Conflict-Free Constraint: The selected team must be strictly conflict-free; no
two coders in the selected subset can have a predefined rivalry.

Team Size: A team can consist of any number of coders, from just one individual
to the entire available pool.

Objective: Design and implement a heuristic or approximation algorithm that
rapidly evaluates valid combinations and outputs the highest-scoring subset it
can find within the 5-minute execution window.
Input Format
The first line contains two integers N and M — the total number of available
coders and the number of conflict pairs.

The second line contains N space-separated integers: S₁, S₂, ..., Sₙ, where Sᵢ
represents the skill rating of the i-th coder.

The next M lines each contain two integers: u and v, indicating a mutual conflict
between coder u and coder v

Output Format
The first line must contain a single integer — the total sum of skill ratings for
your selected, conflict-free team.

The second line should list the space-separated indices of the selected coders
in ascending order to prove the team composition.

(Note: Your solution will be judged based on the validity of your team and how
high your score is relative to the best known solutions.)
Constraints
1 <= N <= 200,000

0 <= M <= (N * (N - 1)) / 2

1 <= Sᵢ <= 1,000,000,000

1 <= u, v <= N

u != v

All conflict pairs (u, v) are distinct.
