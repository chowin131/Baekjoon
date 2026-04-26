# [Diamond II] Prefixuffix - 8235 

[문제 링크](https://www.acmicpc.net/problem/8235) 

### 성능 요약

메모리: 38328 KB, 시간: 120 ms

### 분류

문자열, 해싱, 매내처

### 제출 일자

2026년 4월 26일 17:58:14

### 문제 설명

<p>We consider strings consisting of lowercase letters of the English alphabet in this problem. An initial fragment of a given string is called its prefix. A final (terminal) fragment of a given string is called its suffix. In particular, the empty string is both a prefix and a suffix of any string. Two strings are cyclically equivalent if one of them can be obtained from another by moving its certain suffix from the end of the string to its beginning. For example, the strings ababba and abbaab are cyclically equivalent, whereas the strings ababba and ababab are not. In particular, every string is cyclically equivalent to itself.</p>

<p>A string t consisting of n letters is given. We are looking for its prefix p and suffix s of equal length such that:</p>

<ul>
	<li>p and s are cyclically equivalent,</li>
	<li>the common length of p and s does not exceed <mjx-container class="MathJax" jax="CHTML" style="font-size: 99.9%; position: relative;"><mjx-math class="MJX-TEX" aria-hidden="true"><mjx-mfrac><mjx-frac><mjx-num><mjx-nstrut></mjx-nstrut><mjx-mi class="mjx-i" size="s"><mjx-c class="mjx-c1D45B TEX-I"></mjx-c></mjx-mi></mjx-num><mjx-dbox><mjx-dtable><mjx-line></mjx-line><mjx-row><mjx-den><mjx-dstrut></mjx-dstrut><mjx-mn class="mjx-n" size="s"><mjx-c class="mjx-c32"></mjx-c></mjx-mn></mjx-den></mjx-row></mjx-dtable></mjx-dbox></mjx-frac></mjx-mfrac></mjx-math><mjx-assistive-mml unselectable="on" display="inline"><math xmlns="http://www.w3.org/1998/Math/MathML"><mfrac><mi>n</mi><mn>2</mn></mfrac></math></mjx-assistive-mml><span aria-hidden="true" class="no-mathjax mjx-copytext">\( \frac {n}{2} \)</span></mjx-container>(i.e., the prefix p and the suffix s do not overlap in t), and</li>
	<li>the common length of p and s is maximized.</li>
</ul>

### 입력 

 <p>The first line of the standard input contains a single integer n (1 ≤ n ≤ 1,000,000) denoting the length of the string t. The second line of input contains the string t itself, consisting of n lowercase letters of the English alphabet.</p>

### 출력 

 <p>Your program should print a single integer in the first and only line of the standard output, namely the common length of the prefix p and the suffix s that we are looking for.</p>

