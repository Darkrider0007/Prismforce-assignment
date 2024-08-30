#include <iostream>
#include <vector>
using namespace std;

const int totalCircles = 11; // total number of circles in the chakravyuha

int abhimanyuPower; // initial power of Abhimanyu

// Function declarations
bool handleRearEnemy(int& currentPower, int& rearEnemy);
bool skipCircle(vector<int>& circlePower, int currentCircle, int currentPower, int skipsRemaining, int rechargesRemaining, int rearEnemy);
bool fightCircle(vector<int>& circlePower, int currentCircle, int& currentPower, int skipsRemaining, int rechargesRemaining, int& rearEnemy);
bool canAbhimanyuCross(vector<int>& circlePower, int currentCircle, int currentPower, int skipsRemaining, int rechargesRemaining, int rearEnemy);

// Function to handle enemy attacks from behind
bool handleRearEnemy(int& currentPower, int& rearEnemy) {
    if (currentPower >= rearEnemy) {
        currentPower -= rearEnemy;
        rearEnemy = 0;
        return true;
    }
    return false;
}

// Function to handle skipping a circle
bool skipCircle(vector<int>& circlePower, int currentCircle, int currentPower, int skipsRemaining, int rechargesRemaining, int rearEnemy) {
    if (skipsRemaining > 0) {
        return canAbhimanyuCross(circlePower, currentCircle + 1, currentPower, skipsRemaining - 1, rechargesRemaining, rearEnemy);
    }
    return false;
}

// Function to handle fighting in a circle
bool fightCircle(vector<int>& circlePower, int currentCircle, int& currentPower, int skipsRemaining, int rechargesRemaining, int& rearEnemy) {
    if (currentPower >= circlePower[currentCircle]) {
        if (currentCircle == 2 || currentCircle == 6) {
            rearEnemy = circlePower[currentCircle] / 2; // Set up the rear attack.
        }
        return canAbhimanyuCross(circlePower, currentCircle + 1, currentPower - circlePower[currentCircle], skipsRemaining, rechargesRemaining, rearEnemy);
    }
    return false;
}

// Function to check if Abhimanyu can pass through the chakravyuha
bool canAbhimanyuCross(vector<int>& circlePower, int currentCircle, int currentPower, int skipsRemaining, int rechargesRemaining, int rearEnemy) {
    // Base case: all circles are defeated.
    if (currentCircle == totalCircles)
        return true;

    bool canCross = false;

    // Option 1: Recharge if available and beneficial.
    if (rechargesRemaining > 0 && currentPower < abhimanyuPower) {
        canCross |= canAbhimanyuCross(circlePower, currentCircle, abhimanyuPower, skipsRemaining, rechargesRemaining - 1, rearEnemy);
    }

    // Handle rear enemy attack if applicable.
    if (!handleRearEnemy(currentPower, rearEnemy)) {
        return false;
    }

    // Option 2: Skip the current circle if skips are available.
    canCross |= skipCircle(circlePower, currentCircle, currentPower, skipsRemaining, rechargesRemaining, rearEnemy);

    // Option 3: Fight the current circle.
    canCross |= fightCircle(circlePower, currentCircle, currentPower, skipsRemaining, rechargesRemaining, rearEnemy);

    return canCross;
}

int main() {
    vector<int> circlePower(totalCircles); // Powers of each enemy in the chakravyuha.

    for (int i = 0; i < totalCircles; i++)
        cin >> circlePower[i];

    int maxSkips, maxRecharges; // Maximum skips and recharges available.
    cin >> abhimanyuPower >> maxSkips >> maxRecharges;

    // Ensure skips and recharges do not exceed the number of circles.
    maxSkips = min(maxSkips, totalCircles);
    maxRecharges = min(maxRecharges, totalCircles);

    // Check if Abhimanyu can successfully cross the chakravyuha.
    if (canAbhimanyuCross(circlePower, 0, abhimanyuPower, maxSkips, maxRecharges, 0))
        cout << "Abhimanyu successfully crossed the chakravyuha!" << endl;
    else
        cout << "Abhimanyu could not cross the chakravyuha." << endl;

    return 0;
}
/*
Test Case 1 (Success):
circlePower = [3, 6, 4, 5, 3, 7, 6, 4, 2, 3, 1]
abhimanyuPower = 12
skipsRemaining = 2
rechargesRemaining = 2

Output:
Abhimanyu successfully crossed the chakravyuha!

Test Case 2 (Failure):
Description: The initial power is insufficient, and recharges are limited.
Input:
circlePower = [5, 7, 8, 4, 3, 6, 5, 9, 10, 4, 2]
abhimanyuPower = 6
skipsRemaining = 1
rechargesRemaining = 1
Explanation: With limited initial power and recharges, Abhimanyu will struggle to get past several enemies, and even though he has one skip, he may not be able to cross all enemies.
Output:
Abhimanyu could not cross the chakravyuha.
*/
