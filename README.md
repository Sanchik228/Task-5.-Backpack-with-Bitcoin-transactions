# Task #5. Backpack with Bitcoin transactions

Problem Statement:
You are developing a component of a Bitcoin mining software. Your task is to select transactions for a new block in such a way that:
- The block size must not exceed **1 MB** (1,000,000 bytes).
- Each transaction has a **size (in bytes)** and a **fee (in satoshis)**.
- You must **maximize the total fee** extracted from the selected transactions.

Input:
The program reads a CSV file with up to **100,000** transactions. Each line in the file has the format:
tx_id,tx_size,tx_fee
Example:
a1b2c3,500,3000
b2c3d4,800,4000
c3d4e5,200,1000

Output
The console output displays:
- Number of transactions in the block
- Total block size (≤ 1,000,000 bytes)
- Total fee collected
- Time taken to construct the block (in microseconds)
- Total number of transactions read

How to Run:
1. Transfer the necessary data to “transactions.csv” in the format as shown in the example.
2. Compile the program (e.g., in Visual Studio or using g++).
3. Run the program.

Algorithm Description:
The algorithm uses a greedy strategy:
Sort all transactions by fee per byte in descending order.
Add transactions one by one to the block until the size limit (1 MB) is reached.
Why this is efficient:
Transactions that provide more fee per byte are more profitable and should be prioritized.
Greedy approach gives a very good approximation of the optimal solution in this context.
Sorting takes O(n log n) time, and selecting transactions takes O(n).

Time Complexity:
Sorting transactions: O(n log n)
Selecting transactions for block: O(n)
Total complexity: O(n log n), where n is the number of transactions.
Space Complexity
All transactions are stored in memory → O(n)
The selected block also takes up to O(n)