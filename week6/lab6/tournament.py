# Simulate a sports tournament

import csv
import sys
import random

# Number of simluations to run
N = 1000


def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    teams = []
    # TODO: Read teams into memory from file
    team_dic = {}
    with open(sys.argv[1]) as csvfile:
        reader = csv.DictReader(csvfile)
        for row in reader:
            del team_dic
            team_dic = {}
            team_dic["team"] = row["team"]
            team_dic["rating"] = int(row["rating"])
            teams.append(team_dic)

    counts = {}
    # TODO: Simulate N tournaments and keep track of win counts
    for i in range(0, N, 1):
        winner = simulate_tournament(teams)
        if winner in counts.keys():
            counts[winner] += 1
        else:
            counts[winner] = 1

    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])

    return winners


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""
    # TODO
    qty_rounds = 1
    qty_rounds_tmp = len(teams)
    while (qty_rounds_tmp // 2 > 1):
        qty_rounds += 1
        qty_rounds_tmp //= 2
    winner_tmp = (simulate_round(teams))[:]
    for i in range(0, qty_rounds - 1, 1):
        tmp = winner_tmp[:]
        winner_tmp = (simulate_round(tmp))[:]

    winner = winner_tmp[0]["team"]
    return winner


# call it:
# python tournament.py 2018m.csv


if __name__ == "__main__":
    main()