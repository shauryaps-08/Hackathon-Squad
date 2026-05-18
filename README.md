# Hackathon Squad

This was my solution for the Hackathon Squad problem given by the Coding Club, IIT Guwahati as part of Even Semester Projects 2026.

## What the problem is asking

You have N coders each with a skill rating and some of them refuse to work together. You need to pick a team with the highest possible total skill without including any conflicting pairs.

Sounds simple but its actually a really well known hard problem in computer science called Maximum Weight Independent Set. There's no known way to solve it perfectly for large inputs in any reasonable time, so the problem itself says just do your best within 5 minutes.

## How I approached it

I used three things stacked on top of each other.

**Greedy to start** — sort coders by skill rating highest first and keep picking whoever doesn't conflict with the current team. Fast but not always optimal since being greedy early can block better combinations later.

**Local Search to improve** — go through each coder in the team and ask "what if I drop this person and add their neighbors instead?" If the neighbors together score more than the person I dropped, make the swap. Keep doing this until no swap helps anymore.

**Shake and repeat for 5 minutes** — once local search gets stuck, randomly remove a few coders to shake things up and run local search again from there. The longer I stay stuck the harder I shake. If nothing works after a while I restart completely from scratch with a reshuffled greedy. I keep track of the best score seen across all attempts.

