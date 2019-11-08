const expression = `for i:=1 to n+m do begin d:=j;end;`;

const invalidVariables = [];
const words = `and array begin continue case const div do downto else end file for function goto if in label mod nil not of or packed procedure program record repeat set then to type until var while with integer char real string boolean array file set record enumerated subrange exit sin cos`;
const reservedWordsList = words.split(" ");
const comments = [];
const validVariables = [];
const reservedWords = [];
const symbols = [];
const realNumbers = [];
const ariphmeticOperandsArr = [];
const integerNumbers = [];
const prohibitedSymbolsArr = [];

const doubleSymbols = /(:=)|(\+=)|(-=)|(\*=)|(\/=)|(<<)|(>>)|(\+\+)|(--)|(<=)|(>=)/;

// const expression = `b2*a[n]; b:=d;`;
const symbolsRegex = /[\,\.\;\:\(\)\[\]\=\<\>\/]{1}/;
// console.log(expression.match(symbolsRegex));
const ariphmeticOperands = /[\-\*\+\/]/;
const varRegex = /[A-Za-z_]+[0-9_A-Za-z]*/;
const prohibitedSymbols = /[&$#@!]/;
// const numberRegex = /\d+|(\d+)(\.\d+)(e(\+|-)?(\d+))?|(\d+)(\.\d+)e(\+|-)?|(\d+)e(\+|-)?|(\d+)(e(\+|-)?(\d+))?/;
const integerRegex = /\d+/;
//const floatRegex = /(\d+)(\.\d+)(e(\+|-)?(\d+))?|(\d+)(\.\d+)e(\+|-)?|(\d+)e(\+|-)?|(\d+)e(\+|-)?(\d+)?/;
const floatRegex = /[0-9]+[.][0-9]+/g;
const commentsRegex = /(\/\/.*\n?)|\(\*(.|\n)*?\*\)|\{(.|\n)*?\}|\{(.|\n)*|\(\*(.|\n)*/;
const invRegex = /^[0-9]+[A-Za-z!\u0400-\u04FF]+|[A-Za-z!]+[\u0400-\u04FF!]+[A-Za-z!]+|[!\u0400-\u04FF]+[!A-Za-z]+|[!A-Za-z]+[!\u0400-\u04FF]|!+[A-Za-z]+|[A-Za-z]+!+[A-Za-z]+|[A-Za-z]+!+|[\u0400-\u04FF]+/;

const lexemsMap = new Map();
// const regx = /\d+[A-Za-z\,\.\;\:\(\)\[\]\+\+=\:=\-\-=\<\>\*\/]+/; //! Locates a word starting with a digit
// const regx1 = /[\,\.\;\:\{\}\(\)\[\]\+\+=\:=\-\-=\<\>\*\/]+[A-Za-z\,\.\;\:\{\}\(\)\[\]\+\+=\:=\-\-=\<\>\*\/]*/; //!Locates a word that starts with an invalid symbol
// const regx2 = /[A-Za-z]+[0-9\,\.\d;\:\{\}\(\)\[\]\+\+=\:=\-\-=\<\>\*\/]+[0-9A-Za-z\,\.\;\:\{\}\(\)\[\]\+\+=\:=\-\-=\<\>\*\/]*/; //! Locates a word starting with a letter and containing invalid symbols
findComments = str => {
  let lastMatch = str.match(commentsRegex);
  while (lastMatch !== null) {
    comments.push(lastMatch[0]);
    // lexemsMap.set(lastMatch.index, "T_COMMENT");
    str = str.replace(lastMatch[0], " ".repeat(lastMatch[0].length));
    lastMatch = str.match(commentsRegex);
  }
  return str;
};

findInvalidVariables = str => {
  let lastMatch = str.match(invRegex);
  while (lastMatch !== null) {
    lexemsMap.set(lastMatch.index, "T_INVALID_VARIABLE");
    invalidVariables.push(lastMatch[0]);
    str = str.replace(lastMatch[0], " ");
    lastMatch = str.match(invRegex);
  }
  return str;
};

// const newStr = " ".repeat(10);
// console.log(newStr.length);

findValidVariablesAndReservedWords = str => {
  let possVarMatch = str.match(varRegex);
  while (possVarMatch !== null) {
    let flagReserved = false;
    for (const reswordIndex in reservedWordsList) {
      if (possVarMatch[0] === reservedWordsList[reswordIndex]) {
        reservedWords.push(possVarMatch[0]);
        // let lexemType;
        // if (possVarMatch === "if")  lexemType = "T_IF"
        // if (possVarMatch === "case")  lexemType = "T_CASE"
        // if (possVarMatch === "if")  lexemType = "T_IF"
        // if (possVarMatch === "if")  lexemType = "T_IF"
        // if (possVarMatch === "if")  lexemType = "T_IF"
        if (
            possVarMatch[0] === "sin" || 
            possVarMatch[0] === "cos"
          ) {
          lexemsMap.set(possVarMatch.index, "T_MATH_OPERATION");
        }
        if (
          possVarMatch[0] === "for"
        ) {
        lexemsMap.set(possVarMatch.index, "T_FOR");
        }
        if (
          possVarMatch[0] === "to"
        ) {
        lexemsMap.set(possVarMatch.index, "T_TO");
        }
        if (
          possVarMatch[0] === "if"
        ) {
        lexemsMap.set(possVarMatch.index, "T_IF");
        }
        if (
          possVarMatch[0] === "then"
        ) {
        lexemsMap.set(possVarMatch.index, "T_THEN");
        }
        if (
          possVarMatch[0] === "begin"
        ) {
        lexemsMap.set(possVarMatch.index, "T_BEGIN");
        }
        if (
          possVarMatch[0] === "end"
        ) {
        lexemsMap.set(possVarMatch.index, "T_END");
        }
        if(lexemsMap.get(possVarMatch.index) === undefined) 
        lexemsMap.set(possVarMatch.index, "T_RESERVED_WORD");
        str = str.replace(possVarMatch[0], " ".repeat(possVarMatch[0].length));
        possVarMatch = str.match(varRegex);
        flagReserved = true;
        break;
      }
    }
    if (!flagReserved) {
      validVariables.push(possVarMatch[0]);
      lexemsMap.set(possVarMatch.index, "T_VARIABLE");
      str = str.replace(possVarMatch[0], " ".repeat(possVarMatch[0].length));
      possVarMatch = str.match(varRegex);
    }
  }

  return str;
};

findSymbols = str => {
  let possSymbMatch = str.match(doubleSymbols);
  while (possSymbMatch !== null) {
    symbols.push(possSymbMatch[0]);
    if ([":=", "+=", "-=", "*=", "/="].includes(possSymbMatch[0]))
      lexemsMap.set(possSymbMatch.index, "T_ASSIGNMENT");
    if ([">>", "<<"].includes(possSymbMatch[0]))
      lexemsMap.set(possSymbMatch.index, "T_SHIFT");
    if (["++", "--"].includes(possSymbMatch[0]))
      lexemsMap.set(possSymbMatch.index, "T_UNARY_OPERATOR");
      if (
        possSymbMatch[0] === "<=" ||
        possSymbMatch[0] === ">=")
        lexemsMap.set(possSymbMatch.index, "T_COMPARSION");
    str = str.replace(possSymbMatch[0], " ".repeat(possSymbMatch[0].length));
    possSymbMatch = str.match(doubleSymbols);
    // console.log(lexemsMap);
  }

  possSymbMatch = str.match(ariphmeticOperands);
  while (possSymbMatch !== null) {
    ariphmeticOperandsArr.push(possSymbMatch[0]);
    if (["+", "-", "*", "/"].includes(possSymbMatch[0]))
      lexemsMap.set(possSymbMatch.index, "T_BINARY_OPERATOR");
    str = str.replace(possSymbMatch[0], " ");
    possSymbMatch = str.match(ariphmeticOperands);
  }

  possSymbMatch = str.match(prohibitedSymbols);
  while (possSymbMatch !== null) {
    lexemsMap.set(possSymbMatch.index, "T_PROHIBITED_SYMBOL");
    prohibitedSymbolsArr.push(possSymbMatch[0]);
    str = str.replace(possSymbMatch[0], " ");
    possSymbMatch = str.match(prohibitedSymbols);
  }

  possSymbMatch = str.match(symbolsRegex);
  while (possSymbMatch !== null) {
    // console.log(possSymbMatch);
    symbols.push(possSymbMatch[0]);
    if (possSymbMatch[0] === "(")
      lexemsMap.set(possSymbMatch.index, "T_LEFT_PARENTHESIS");
    if (possSymbMatch[0] === ")")
      lexemsMap.set(possSymbMatch.index, "T_RIGHT_PARENTHESIS");
    if (possSymbMatch[0] === "[")
      lexemsMap.set(possSymbMatch.index, "T_LEFT_BRACKET");
    if (possSymbMatch[0] === "]")
      lexemsMap.set(possSymbMatch.index, "T_RIGHT_BRACKET");
    if (possSymbMatch[0] === ":")
      lexemsMap.set(possSymbMatch.index, "T_COLUMN");
    if (possSymbMatch[0] === ";")
      lexemsMap.set(possSymbMatch.index, "T_SEMICOLUMN");
    if (
      possSymbMatch[0] === "<" ||
      possSymbMatch[0] === ">" ||
      possSymbMatch[0] === "=")
      lexemsMap.set(possSymbMatch.index, "T_COMPARSION");
      
    if (!lexemsMap.has(possSymbMatch.index))
      lexemsMap.set(possSymbMatch.index, "T_SYMBOL");
    str = str.replace(possSymbMatch[0], " ");
    possSymbMatch = str.match(symbolsRegex);
  }
  return str;
};

findNumbers = str => {
  let possNumbMatch = str.match(floatRegex);

  while (possNumbMatch !== null) {
    realNumbers.push(possNumbMatch[0]);
    lexemsMap.set(possNumbMatch.index, "T_FLOAT");
    str = str.replace(possNumbMatch[0], " ".repeat(possNumbMatch[0].length));
    possNumbMatch = str.match(floatRegex);
  }

  possNumbMatch = str.match(integerRegex);
  while (possNumbMatch !== null) {
    integerNumbers.push(possNumbMatch[0]);
    lexemsMap.set(possNumbMatch.index, "T_INTEGER");
    str = str.replace(possNumbMatch[0], " ".repeat(possNumbMatch[0].length));
    possNumbMatch = str.match(integerRegex);
  }

  return str;
};

console.log("\n Input expression:");
console.log(expression);

const withoutComments = findComments(expression);
const withoutInvalidVariables = findInvalidVariables(withoutComments);
const withoutVariablesAndReservedWords = findValidVariablesAndReservedWords(
  withoutInvalidVariables
);
const withoutNumbers = findNumbers(withoutVariablesAndReservedWords);
const withoutSymbols = findSymbols(withoutNumbers);

const lexemsSortedMap = new Map(
  [...lexemsMap.entries()].sort((a, b) => a[0] - b[0])
);
const lexemsTable = [...lexemsSortedMap.entries()].map(e => e[1]);
const lexemsIndexes = [...lexemsSortedMap.entries()].map(e => e[0]);

const checkSyntax = (lexemsTable, index) => {
  let errorOccured = false;

  if (lexemsTable[lexemsTable.length   - 1] !== "T_SEMICOLUMN") {
    errorOccured = true;
    console.log(
      `ERROR at ${
        lexemsIndexes[lexemsTable.length - 1]
      } You have to place semicolumn at the end`
    );
  }

  if (lexemsTable[index] === "T_VARIABLE") {
    if (lexemsTable[index + 1] === "T_VARIABLE") {
      errorOccured = true;
      console.log(
        `ERROR at ${
          lexemsIndexes[index + 1]
        } You can't place two variables in a row`
      );
    }
    if (
      lexemsTable[index + 1] === "T_BINARY_OPERATOR" &&
      (
        lexemsTable[index - 1] !== "T_TO" && 
          (
            (
            lexemsTable[index - 1] !== "T_ASSIGNMENT" &&
            (lexemsTable[index - 1] !== "T_LEFT_PARENTHESIS" &&
            lexemsTable[index - 2] !== "T_MATH_OPERATION")
            )
          )
      )

    ) {
      // console.log(lexemsTable[index - 1] !== "T_TO" )
      errorOccured = true;
      console.log(
        `ERROR at ${
          lexemsIndexes[index + 1]
        } You can't use BINARY OPERATOR without ASSIGNMENT OPERATOR before`
      );
    }
    if (
      lexemsTable[index + 1] === "T_FLOAT" ||
      lexemsTable[index + 1] === "T_INTEGER"
    ) {
      errorOccured = true;
      console.log(
        `ERROR at ${
          lexemsIndexes[index + 1]
        } You can't use DIGITS right after a VARIABLE`
      );
    }
    // if (
    //   lexemsTable[index + 1] === "T_COMPARSION" ||
    //   lexemsTable[index + 1] === "T_INTEGER"
    // ) {
    //   errorOccured = true;
    //   console.log(
    //     `ERROR at ${
    //       lexemsIndexes[index + 1]
    //     } You can't use DIGITS right after a VARIABLE`
    //   );
    // }

  }
  if (lexemsTable[index] === "T_LEFT_BRACKET") {
    if (lexemsTable[index + 1] === "T_RIGHT_BRACKET") {
      errorOccured = true;
      console.log(
        `ERROR at index ${
          lexemsIndexes[index + 1]
        } You can't use empty brackets`
      );
    }
    if (lexemsTable[index + 1] === "T_LEFT_BRACKET") {
      errorOccured = true;
      console.log(
        `ERROR at index ${
          lexemsIndexes[index + 1]
        } You can't open one more brackets here`
      );
    }
    if (
      lexemsTable[index + 1] === "T_ASSIGNMENT" ||
      lexemsTable[index + 1] === "T_BINARY_OPERATOR" ||
      lexemsTable[index + 1] === "T_UNARY_OPERATOR" ||
      lexemsTable[index + 1] === "T_SYMBOL" ||
      lexemsTable[index + 1] === "T_COLUMN" ||
      lexemsTable[index + 1] === "T_SEMICOLUMN"
    ) {
      errorOccured = true;
      console.log(
        `ERROR at index ${
          lexemsIndexes[index + 1]
        } : Wrong symbols after opened bracket`
      );
    }
    if (
      lexemsTable[index - 1] !== "T_VARIABLE" &&
      lexemsTable[index - 1] !== "T_RIGHT_BRACKET"
    ) {
      errorOccured = true;
      console.log(
        `ERROR at ${lexemsIndexes[index]} index : You can't open bracket here`
      );
    }
  }
  if (lexemsTable[index] === "T_RIGHT_BRACKET") {
    if (
      lexemsTable[index - 1] !== "T_VARIABLE" &&
      lexemsTable[index - 1] !== "T_FLOAT" &&
      lexemsTable[index - 1] !== "T_INTEGER" &&
      lexemsTable[index - 1] !== "T_UNARY_OPERATOR" &&
      lexemsTable[index - 1] !== "T_RIGHT_PARENTHESIS" &&
      lexemsTable[index - 1] !== "T_RIGHT_BRACKET"
    ) {
      errorOccured = true;
      console.log(
        `ERROR at ${lexemsIndexes[index]} index:  You can't close bracket here`
      );
    }
    if (
      lexemsTable[index + 1] !== "T_SEMICOLUMN" &&
      lexemsTable[index + 1] !== "T_BINARY_OPERATOR" &&
      lexemsTable[index + 1] !== "T_UNARY_OPERATOR" &&
      lexemsTable[index + 1] !== "T_RIGHT_BRACKET" &&
      lexemsTable[index + 1] !== "T_LEFT_BRACKET" &&
      lexemsTable[index + 1] !== "T_RIGHT_PARENTHESIS"
    ) {
      errorOccured = true;
      console.log(
        `ERROR at ${lexemsIndexes[index]} index : Invalid symbol after closing bracket `
      );
    }
    if (lexemsTable[index + 1] === "T_BINARY_OPERATOR") {
      const leftBr = findBracketLeftPair(index);
      if (
        lexemsTable[leftBr - 2] !== "T_BINARY_OPERATOR" &&
        lexemsTable[leftBr - 2] !== "T_ASSIGNMENT"
      ) {
        errorOccured = true;
        console.log(
          `ERROR at ${lexemsIndexes[index]} index : You cant use binary operator here `
        );
      }
    }
  }
  if (lexemsTable[index] === "T_LEFT_PARENTHESIS") {
    if (
      lexemsTable[index - 1] !== "T_ASSIGNMENT" &&
      lexemsTable[index - 1] !== "T_BINARY_OPERATOR" &&
      lexemsTable[index - 1] !== "T_LEFT_BRACKET" &&
      lexemsTable[index - 1] !== "T_VARIABLE" &&
      lexemsTable[index - 1] !== "T_MATH_OPERATION" &&
      lexemsTable[index - 1] !== "T_LEFT_PARENTHESIS"
    ) {
      errorOccured = true;
      console.log(
        `ERROR at ${lexemsIndexes[index]} index:  You can't open parenthesis here`
      );
    }

    if (
      lexemsTable[index + 1] === "T_RIGHT_PARENTHESIS" &&
      lexemsTable[index - 1] !== "T_VARIABLE"
    ) {
      errorOccured = true;
      console.log(
        `ERROR at index ${
          lexemsIndexes[index + 1]
        } : You can't use empty parenthesis`
      );
    }
  }
  if (lexemsTable[index] === "T_RIGHT_PARENTHESIS") {
  }
  if (lexemsTable[index] === "T_RESERVED_WORD") {
  }
  if (lexemsTable[index] === "T_ASSIGNMENT") {
    if (lexemsTable[index + 1] === "T_ASSIGNMENT") {
      errorOccured = true;
      console.log(
        `ERROR at ${
          lexemsIndexes[index + 1]
        } index:  You can't use 2 and more assignment operators in a row`
      );
    }
    if (
      lexemsTable[index + 1] !== "T_VARIABLE" &&
      lexemsTable[index + 1] !== "T_LEFT_PARENTHESIS" &&
      lexemsTable[index + 1] !== "T_MATH_OPERATION" &&
      lexemsTable[index + 1] !== "T_FLOAT" &&
      lexemsTable[index + 1] !== "T_INTEGER"
    ) {
      errorOccured = true;
      console.log(
        `ERROR at ${
          lexemsIndexes[index + 1]
        } index:  Invalid lexems after ASSIGNMENT`
      );
    }
    if (lexemsTable[index - 1] !== "T_VARIABLE") {
      errorOccured = true;
      console.log(
        `ERROR at ${lexemsIndexes[index]} index:  You can use assignment operator only after a variable`
      );
    }
    if (lexemsTable[index - 1] === "T_RESERVED_WORD") {
      errorOccured = true;
      console.log(
        `ERROR at ${lexemsIndexes[index]} index:  You can't use assignment operator after a keyword`
      );
    }
    let semicolumn = 0;
    let assignment = 0;
    for (let i = index - 1; i > 0; i--) {
      if (lexemsTable[i] === "T_SEMICOLUMN") {
        semicolumn = i;
        break;
      }
    }
    for (let i = index - 1; i > 0; i--) {
      if (lexemsTable[i] === "T_ASSIGNMENT") {
        assignment = i;
        break;
      }
    }
    if (assignment > semicolumn && assignment !== 0 && semicolumn !== 0) {
      errorOccured = true;

      console.log(
        `ERROR at ${lexemsIndexes[index]} index:  You can't use assignment operator here`
      );
    }
    if (lexemsTable === "T_ASSIGNMENT") {
      errorOccured = true;
      console.log(
        `ERROR at ${
          lexemsIndexes[index + 1]
        } index:  You can't use 2 and more assignment operators in a row`
      );
    }
  }
  if (lexemsTable[index] === "T_RESERVED_WORD") {
  }
  if (lexemsTable[index] === "T_UNARY_OPERATOR") {
  }
  if (lexemsTable[index] === "T_BINARY_OPERATOR") {
    if (
      (lexemsTable[index - 1] !== "T_FLOAT" &&
        lexemsTable[index - 1] !== "T_INTEGER" &&
        lexemsTable[index - 1] !== "T_VARIABLE" &&
        lexemsTable[index - 1] !== "T_RIGHT_PARENTHESIS") ||
      (lexemsTable[index + 1] !== "T_FLOAT" &&
        lexemsTable[index + 1] !== "T_INTEGER" &&
        lexemsTable[index + 1] !== "T_VARIABLE" &&
        lexemsTable[index + 1] !== "T_LEFT_PARENTHESIS")
    ) {
      errorOccured = true;
      console.log(
        `ERROR at ${lexemsIndexes[index]} index:  BINARY OPERATOR requires TWO operands`
      );
    }
  }
  if (lexemsTable[index] === "T_SEMICOLUMN") {
    if (lexemsTable[index - 1] === "T_SEMICOLUMN") {
      errorOccured = true;
      console.log(
        `ERROR at ${lexemsIndexes[index]} index:  You can't use two semicolumns in a row`
      );
    }
  }
  if (lexemsTable[index] === "T_COLUMN") {
  }
  if (lexemsTable[index] === "T_END") {
    if (lexemsTable[index + 1] !== "T_SEMICOLUMN") {
      errorOccured = true;
      console.log(
        `ERROR at ${lexemsIndexes[index]} index: You have to place a semicolumn after 'end' `
      );
    }
  }
  if (lexemsTable[index] === "T_SYMBOL") {
  }

  if (lexemsTable[index] === "T_FLOAT" || lexemsTable[index] === "T_INTEGER") {
    if (lexemsTable[index + 1] === "T_VARIABLE") {
      errorOccured = true;
      console.log(
        `ERROR at ${lexemsIndexes[index]} index: You can't place variable right after a number `
      );
    }
    if (
      lexemsTable[index + 1] === "T_BINARY_OPERATOR" &&
      (
        lexemsTable[index - 1] !== "T_TO" && 
          (
            (
            lexemsTable[index - 1] !== "T_ASSIGNMENT" &&
            (lexemsTable[index - 1] !== "T_LEFT_PARENTHESIS" &&
            lexemsTable[index - 2] !== "T_MATH_OPERATION")
            )
          )
      )

    ) {
      errorOccured = true;
      console.log(
        `ERROR at ${
          lexemsIndexes[index + 1]
        } index : You can't use BINARY OPERATOR without ASSIGNMENT OPERATOR before`
      );
    }
  }

  if(lexemsTable[index] === "T_FOR"){
    if(lexemsTable[index + 1] === "T_VARIABLE"){
      if(lexemsTable[index + 2] === "T_ASSIGNMENT"){
        if(
            lexemsTable[index + 3] !== "T_VARIABLE" &&
            lexemsTable[index + 3] !== "T_INTEGER" &&
            lexemsTable[index + 3] !== "T_LEFT_PARENTHESIS"
          ){
            console.log(
              `ERROR at ${
                lexemsIndexes[index + 3]
              } index : You can't use it after ASSIGNMENT OPERATOR`
            );    
        }
        
        let newIndex = index + 3;
        
        if(lexemsTable[index + 3] === "T_LEFT_PARENTHESIS"){
          newIndex = findParenthesisRightPair(index+3);
        
        }
        if(
          lexemsTable[index + 3] === "T_VARIABLE" &&
          lexemsTable[index + 4] === "T_LEFT_PARENTHESIS"
          ){
            newIndex = findParenthesisRightPair(index+4);
        }
        if(
          lexemsTable[index + 3] === "T_VARIABLE" &&
          lexemsTable[index + 4] === "T_LEFT_BRACKET"
          ){
            newIndex = findBracketRightPair(index+4);
        }
        console.log(newIndex)
        console.log(lexemsIndexes)

      }
    }
  }

  if (!errorOccured && index <= lexemsTable.length) {
    // console.log(index);
    // console.log("Moving on");
    checkSyntax(lexemsTable, index + 1);
  }
  if (!errorOccured && index > lexemsTable.length) {
    console.log(`\n~~~~~Anylize completed successfully~~~~~`);
  }
};

findParenthesisLeftPair = index => {
  let prPairs = 1;
  let leftPr = 0;
  let rightPr = index;
  for (let i = rightPr - 1; i > 0; i--) {
    if (lexemsTable[i] === "T_RIGHT_PARENTHESIS") {
      prPairs++;
      // if (prPairs === 1) leftPr = i;
    }
    if (lexemsTable[i] === "T_LEFT_PARENTHESIS") {
      if (prPairs === 1) {
        leftPr = i;
        break;
      } else if (prPairs > 1) prPairs--;
    }
  }
  return leftPr;
};
findParenthesisRightPair = index => {
  let prPairs = 1;
  let leftPr = index;
  let rightPr = 0;
  for (let i = leftPr + 1; i < lexemsTable.length; i++) {
    if (lexemsTable[i] === "T_LEFT_PARENTHESIS") {
      prPairs++;
      // if (prPairs === 1) leftPr = i;
    }
    if (lexemsTable[i] === "T_RIGHT_PARENTHESIS") {
      if (prPairs === 1) {
        rightPr = i;
        break;
      } else if (prPairs > 1) prPairs--;
    }
  }
  return rightPr;
};

findBracketLeftPair = index => {
  let prPairs = 1;
  let leftPr = 0;
  let rightPr = index;
  for (let i = rightPr - 1; i > 0; i--) {
    if (lexemsTable[i] === "T_RIGHT_BRACKET") {
      prPairs++;
      // if (prPairs === 1) leftPr = i;
    }
    if (lexemsTable[i] === "T_LEFT_BRACKET") {
      if (prPairs === 1) {
        leftPr = i;
        break;
      } else if (prPairs > 1) prPairs--;
    }
  }
  return leftPr;
};
findBracketRightPair = index => {
  let prPairs = 1;
  let leftPr = index;
  let rightPr = 0;
  for (let i = leftPr + 1; i < lexemsTable.length; i++) {
    if (lexemsTable[i] === "T_LEFT_BRACKET") {
      prPairs++;
      // if (prPairs === 1) leftPr = i;
    }
    if (lexemsTable[i] === "T_RIGHT_BRACKET") {
      if (prPairs === 1) {
        rightPr = i;
        break;
      } else if (prPairs > 1) prPairs--;
    }
  }
  return rightPr;
};

checkBracketsAmount = lexemsTable => {
  let lBr = 0;
  let rBr = 0;
  let lPr = 0;
  let rPr = 0;
  let begin = 0;
  let end = 0;
  lexemsTable.forEach(val => {
    if (val === "T_LEFT_PARENTHESIS") lPr++;
    if (val === "T_RIGHT_PARENTHESIS") rPr++;
    if (val === "T_LEFT_BRACKET") lBr++;
    if (val === "T_RIGHT_BRACKET") rBr++;
    if (val === "T_BEGIN") begin++;
    if (val === "T_END") end++;
  });
  if (lPr !== rPr) return "You have unclosed paranthesis";
  if (lBr !== rBr) return "You have unclosed brackets";
  if (begin !== end) return "You have unpaired amount of 'begin' and 'end'";
  return false;
};

checkBracketsContent = lexemsTable => {
  let prPairs = 0;
  let brPairs = 0;
  let leftPr = 0;
  let rightPr = 0;
  let leftBr = 0;
  let rightBr = 0;

  while (lexemsTable.includes("T_LEFT_PARENTHESIS", leftPr + 1)) {
    // console.log(leftPr);
    prPairs = 0;
    for (let i = leftPr + 1; i < lexemsTable.length; i++) {
      if (lexemsTable[i] === "T_LEFT_PARENTHESIS") {
        prPairs++;
        if (prPairs === 1) leftPr = i;
      }
      if (lexemsTable[i] === "T_RIGHT_PARENTHESIS") {
        if (prPairs === 1) {
          rightPr = i;
          break;
        } else if (prPairs > 1) prPairs--;
      }
    }
    for (let i = leftPr + 1; i < rightPr; i++) {
      if (
        lexemsTable[i] === "T_ASSIGNMENT" ||
        lexemsTable[i] === "T_SYMBOL" ||
        lexemsTable[i] === "T_COLUMN" ||
        lexemsTable[i] === "T_SEMICOLUMN"
      ) {
        return `Prohibited symbols inside of parenthesis ${lexemsIndexes[leftPr]} and ${lexemsIndexes[rightPr]}, at lexems index ${lexemsIndexes[i]}`;
      }
    }
  }

  // let arr= [1,2,3]
  // console.log(arr.includes(2,2));

  while (lexemsTable.includes("T_LEFT_BRACKET", leftBr + 1)) {
    // console.log(leftBr);
    brPairs = 0;
    for (let i = leftBr + 1; i < lexemsTable.length; i++) {
      if (lexemsTable[i] === "T_LEFT_BRACKET") {
        brPairs++;
        if (brPairs === 1) leftBr = i;
      }
      if (lexemsTable[i] === "T_RIGHT_BRACKET") {
        if (brPairs === 1) {
          rightBr = i;
          break;
        } else if (brPairs > 1) brPairs--;
      }
    }
    for (let i = leftBr + 1; i < rightBr; i++) {
      if (
        lexemsTable[i] === "T_ASSIGNMENT" ||
        lexemsTable[i] === "T_SYMBOL" ||
        lexemsTable[i] === "T_COLUMN" ||
        lexemsTable[i] === "T_SEMICOLUMN"
      ) {
        return `Prohibited symbols inside of brackets ${lexemsIndexes[leftBr]} and ${lexemsIndexes[rightBr]}, at lexems index ${lexemsIndexes[i]}`;
      }
    }
    // console.log("completed");
  }
  return false;
};

// console.log(" \nComment strings : ");
// console.log(comments);
// console.log(` \nValid variables : `);
// console.log(validVariables);
// console.log(` \nInvalid variables : `);
// console.log(invalidVariables);
// console.log(` \nReserved keywords :  `);
// console.log(reservedWords);
// console.log(` \nUsed symbols : `);
// console.log(symbols);
// console.log(` \nUsed ariph. operands : `);
// console.log(ariphmeticOperandsArr);
// console.log(` \nUsed prohibited symbols : `);
// console.log(prohibitedSymbolsArr);
// console.log(` \nReal : `);
// console.log(realNumbers);
// console.log(` \nInteger : `);
// console.log(integerNumbers);
console.log(lexemsSortedMap);
// console.log(lexemsTable);

if (invalidVariables.length !== 0) {
  // console.log("There invalid");
  lexemsSortedMap.forEach((val, key) => {
    if (val === "T_INVALID_VARIABLE") {
      console.log(`ERROR: invalid variable at ${key} index`);
    }
  });
} else {
  const brackets = checkBracketsAmount(lexemsSortedMap);
  if (brackets) {
    console.log(`ERROR: ${brackets}`);
  } else {
    const prohibited = checkBracketsContent(lexemsTable);
    if (prohibited) {
      console.log(prohibited);
    } else checkSyntax(lexemsTable, 0);
  }
}
