import * as fs from 'fs';
function solve() {
    const input = fs.readFileSync(0, 'utf8').split('\n');
    if (input.length < 2) return;
    const R: number = parseInt(input[0]);
    const S: number = parseInt(input[1]);
    const totalCupcakes: number = (R * 8) + (S * 3);
    const leftOver: number = totalCupcakes - 28;
    console.log(leftOver);
}
solve();