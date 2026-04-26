# [Diamond V] Origami - 19049 

[문제 링크](https://www.acmicpc.net/problem/19049) 

### 성능 요약

메모리: 67868 KB, 시간: 64 ms

### 분류

매내처, 문자열

### 제출 일자

2026년 4월 26일 15:14:39

### 문제 설명

<p>You are given a piece of paper in the shape of a matrix of size $N \times M$. Every cell is colored in one of 26 possible colors which are represented by lowercase letters of the English alphabet. The piece of paper can be folded in the following way. First, you choose a vertical line between two of its columns or a horizontal line between two of its rows. This line splits the paper into two sides. You then use the line as the folding axis and fold the smaller side of the paper onto the larger one going over the axis.  However, you can only do this if all the cells of the smaller side of the paper have matching colors with their corresponding cells on the other side (in other words, each cell should have the same color as its reflection over the chosen axis). If both sides of the paper are of equal size, you may fold from either side.</p>

<p>You notice that after any number of folding operations, you end up with a contiguous submatrix of the original piece of paper. How many different submatrices of the initial piece of paper can you obtain by doing arbitrarily many folding operations (possibly none)? Two submatrices are considered different if they occupy different coordinates in the initial matrix, even if they have identical color content.</p>

<p style="text-align: center;"><img alt="" src="https://upload.acmicpc.net/8217c4a6-8cee-47e5-a8dd-3da73e3c5a93/-/preview/" style="width: 313px; height: 71px;"></p>

### 입력 

 <p>The first line of input contains two integers $N$ and $M$ ($N, M \ge 1$, $1 \le N \cdot M \le 1\,000\,000$).</p>

<p>Each of the next $N$ lines contains a string of length $M$ consisting of lowercase English letters. Together, these lines describe the given piece of paper.</p>

### 출력 

 <p>Print a single line with a single integer: the number of different submatrices that you can obtain by folding the paper.</p>

