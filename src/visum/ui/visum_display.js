#!/usr/bin/env node

var inputChunks = [];

process.stdin.on('data', function (chunk) {
    inputChunks.push(chunk);
});

//var output = outputJSON = JSON.stringify(cashflow, null, '    ');
process.stdin.on('end', function () {
    var input = JSON.parse(inputChunks.join());

    console.log("Cash Flow Statements");
    for (var i in input.cashflows) {
      var cashflow = input.cashflows[i];
      console.log("\tFrom " + cashflow.from + " to " + cashflow.to);
      for (var j in cashflow.transactions) {
        var transaction = cashflow.transactions[j];
        console.log("\t\t" + transaction.description + ":\t "
            + transaction.lineitem);
      }
    }

    console.log("\nBalance Sheet Statements");
    for (var i in input.balancesheets) {
      var balancesheet = input.balancesheets[i];
      console.log("\tBalance Sheet for " + balancesheet.entity
          + " on " + balancesheet.time);
      for (var j in balancesheet.positions) {
        var position = balancesheet.positions[j];
        console.log("\t\t" + position.description + ":\t "
            + position.lineitem);
      }
    }
});
