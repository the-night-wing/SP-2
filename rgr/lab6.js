const fs = require("fs");

let data = "program newprog;";

const expression =
  " var c: single; a : array [1..3] of single; n,d, c, b:word; begin b:=2*a[n]; b:=d end.";

data += expression;

console.log(expression);

fs.writeFile("expr.pas", data, err => {
  if (err) console.log(err);
  //   console.log("Successfully Written to File.");
});

const addVariablesToTheList = index => {
  const columnIndex = lexemsTable.indexOf("T_COLUMN", index);
  if (columnIndex === -1) {
    throw new Error(`
        \nError at index ${index}, wrong variable declaration \n
        Maybe you wanted to place "BEGIN" here?
        \n
        \n
      `);
  }

  //Компьютер\HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\GraphicsDrivers
  const temporaryVault = [];
  let semiColumnIndex = 0;
  for (let i = index; i < columnIndex; i++) {
    if (validVariables.includes(expressionsTable[i])) {
      console.log({ i }, expressionsTable[i]);
      temporaryVault.push(expressionsTable[i]);
    } else if (
      expressionsTable[i] === "," &&
      lexemsTable[i + 1] !== "T_VARIABLE"
    ) {
      throw new Error(`
        \nError at index ${expressionsIndexes[i]}, you can't use "COMMA" here \n\n
      `);
    } else if (expressionsTable[i] !== ",") {
      throw new Error(`
        \nError at index ${expressionsIndexes[i]}, you can't use "${expressionsTable[i]}" as a variable \n\n
      `);
    }
  }
  console.log({ columnIndex });
  if (
    lexemsTable[columnIndex + 1] !== "T_TYPE" &&
    lexemsTable[columnIndex + 1] !== "T_ARRAY"
  ) {
    throw new Error(`
      \nError at index ${
        expressionsIndexes[columnIndex + 1]
      }, you have to define TYPE here \n\n
    `);
  }
  if (expressionsTable[columnIndex + 1] === "array") {
    if (
      expressionsTable[columnIndex + 2] === "[" &&
      lexemsTable[columnIndex + 3] === "T_INTEGER" &&
      lexemsTable[columnIndex + 4] === "T_DOUBLE_DOT" &&
      lexemsTable[columnIndex + 5] === "T_INTEGER" &&
      expressionsTable[columnIndex + 6] === "]"
    ) {
      if (
        lexemsTable[columnIndex + 7] === "T_OF" &&
        lexemsTable[columnIndex + 8] === "T_TYPE" &&
        lexemsTable[columnIndex + 9] === "T_SEMICOLUMN"
      ) {
        semiColumnIndex = columnIndex + 9;
        temporaryVault.forEach(e => {
          if (declaredVariables[e] === undefined) {
            declaredVariables[e] = {
              name: e,
              class: "array",
              type: `${expressionsTable[columnIndex + 8]}`,
              length: +expressionsTable[columnIndex + 5],
              // "length" : (expressionsTable[columnIndex+5].toString()).parseInt(),
              value: Array(+expressionsTable[columnIndex + 5]).fill(0)
            };
          } else {
            throw new Error(`
                      \nError, variable "${e}" has already been declared \n\n
                    `);
          }
        });
      } else {
        throw new Error(`
          \nError at index ${
            expressionsIndexes[columnIndex + 7]
          }, you have to define TYPE of the ARRAY correctly \n\n
        `);
      }
    } else {
      throw new Error(`
      \nError at index ${
        expressionsIndexes[columnIndex + 2]
      }, you have to define ARRAY correctly \n\n
    `);
    }
  } else {
    if (lexemsTable[columnIndex + 2] === "T_SEMICOLUMN") {
      semiColumnIndex = columnIndex + 2;
      temporaryVault.forEach(e => {
        if (declaredVariables[e] === undefined) {
          declaredVariables[e] = {
            name: e,
            class: "variable",
            type: `${expressionsTable[columnIndex + 1]}`,
            value: undefined
          };
        }
      });
    } else {
      throw new Error(`
      \nError at index ${
        expressionsIndexes[columnIndex + 2]
      }, you have to place ";" after TYPE \n\n
    `);
    }
  }
  console.log(declaredVariables);
  console.log({ semiColumnIndex });
  return semiColumnIndex;
};

const checkVar = semiColumnIndex => {
  if (lexemsTable[semiColumnIndex + 1] === "T_BEGIN") {
    return false;
  } else if (lexemsTable[semiColumnIndex + 1] === "T_VARIABLE") {
    return true;
  } else {
    throw new Error(`
    \nError at index ${
      expressionsIndexes[semiColumnIndex + 1]
    }, you have to start you program with "BEGIN" clause\n\n
  `);
  }
};

// const nrc = require("node-run-cmd");
// nrc.run("fpc.exe expr.pas > new.txt");

// require("child_process").exec("cmd /c fpc.exe expr.pas > new.txt");

// fs.readFile("new.txt", function(err, buf) {
//   console.log(buf.toString());
// });
