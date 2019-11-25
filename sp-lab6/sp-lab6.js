// const expression = `For a := 4 to y do begin for g:=1 to s do begin p:=m; end; end;`.toLowerCase()
// const expression = `
// var for i :=1 to n+m do begin d:=j; if (n=m) then begin a:=5 end end. 
// `.toLowerCase();
//!Should i place semicoiumn after end and before else
const expression = `var a, b : array [1..3] of integer ; c,d : real; begin a:=5; b:= a[n]+5; end.`.toLowerCase()
const invalidVariables = [];
const words = `and array begin continue case const div do downto else word shortint longint single byte char boolean extended double end file for function goto if in label mod nil not of or packed procedure program record repeat set then to type until var while with integer char real string boolean array file set record enumerated subrange exit sin cos`;
const reservedWordsList = words.split(" ");
const comments = [];
const validVariables = [];
const reservedWords = [];
const symbols = [];
const realNumbers = [];
const ariphmeticOperandsArr = [];
const integerNumbers = [];
const prohibitedSymbolsArr = [];
const usedTypes = []
const allowedTypes = ["integer", "byte", "word", "shortint", "longint", "real", "single", "double", "extended", "boolean", "char"];
const declaredVariables = {};
let ifAmount = 0;

//!Invalid variable regex works incorrectly

const doubleSymbols = /(:=)|(\+=)|(-=)|(\*=)|(\/=)|(<<)|(>>)|(\+\+)|(--)|(<=)|(>=)|(\.\.)/;

// const expression = `b2*a[n]; b:=d;`;
const comparsionRegex = /[\=\<\>]{1}/ 
const symbolsRegex = /[\,\.\;\:\(\)\[\]\/]{1}/;
// console.log(expression.match(symbolsRegex));
const ariphmeticOperands = /[\-\*\+\/]/;
// const varRegex = /[A-Za-z_]+[0-9_A-Za-z]*/;
const varRegex = /(?<=[^\w])[A-Z]+[A-Z0-9_]*|^[A-Z]+[A-Z0-9_]*/i
const prohibitedSymbols = /[&$#@!]/;
// const numberRegex = /\d+|(\d+)(\.\d+)(e(\+|-)?(\d+))?|(\d+)(\.\d+)e(\+|-)?|(\d+)e(\+|-)?|(\d+)(e(\+|-)?(\d+))?/;
const integerRegex = /\d+/;
//const floatRegex = /(\d+)(\.\d+)(e(\+|-)?(\d+))?|(\d+)(\.\d+)e(\+|-)?|(\d+)e(\+|-)?|(\d+)e(\+|-)?(\d+)?/;
const floatRegex = /[0-9]+[.][0-9]+/g;
const commentsRegex = /(\/\/.*\n?)|\(\*(.|\n)*?\*\)|\{(.|\n)*?\}|\{(.|\n)*|\(\*(.|\n)*/;
// const invRegex = /[0-9]+[A-Za-z!\u0400-\u04FF]+|[A-Za-z!]+[\u0400-\u04FF!]+[A-Za-z!]+|[!\u0400-\u04FF]+[!A-Za-z]+|[!A-Za-z]+[!\u0400-\u04FF]|!+[A-Za-z]+|[A-Za-z]+!+[A-Za-z]+|[A-Za-z]+!+|[\u0400-\u04FF]+/;
const invRegex = /(?<=[^\w])[0-9]+[A-Z]+|^[0-9]+[A-Z]+/i

const lexemsMap = new Map();
const expressionsMap = new Map();
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
        if (possVarMatch[0] === "sin" || possVarMatch[0] === "cos") {
          lexemsMap.set(possVarMatch.index, "T_MATH_OPERATION");
        }
        if (possVarMatch[0] === "for") {
          lexemsMap.set(possVarMatch.index, "T_FOR");
          expressionsMap.set(possVarMatch.index, "for");
        }
        if (possVarMatch[0] === "of") {
          lexemsMap.set(possVarMatch.index, "T_OF");
          expressionsMap.set(possVarMatch.index, "of");
        }
        if (possVarMatch[0] === "to") {
          lexemsMap.set(possVarMatch.index, "T_TO");
          expressionsMap.set(possVarMatch.index, "to");
        }
        if (possVarMatch[0] === "do") {
          lexemsMap.set(possVarMatch.index, "T_DO");
          expressionsMap.set(possVarMatch.index, "do");
        }
        if (possVarMatch[0] === "if") {
          lexemsMap.set(possVarMatch.index, "T_IF");
          expressionsMap.set(possVarMatch.index, "if");
        }
        if (possVarMatch[0] === "then") {
          lexemsMap.set(possVarMatch.index, "T_THEN");
          expressionsMap.set(possVarMatch.index, "then");
        }
        if (possVarMatch[0] === "else") {
          lexemsMap.set(possVarMatch.index, "T_ELSE");
          expressionsMap.set(possVarMatch.index, "else");
        }
        if (possVarMatch[0] === "begin") {
          lexemsMap.set(possVarMatch.index, "T_BEGIN");
          expressionsMap.set(possVarMatch.index, "begin");
        }
        if (possVarMatch[0] === "end") {
          lexemsMap.set(possVarMatch.index, "T_END");
          expressionsMap.set(possVarMatch.index, "end");
        }
        if (possVarMatch[0] === "var") {
          lexemsMap.set(possVarMatch.index, "T_VAR");
          expressionsMap.set(possVarMatch.index, "var");
        }
        if (possVarMatch[0] === "array") {
          lexemsMap.set(possVarMatch.index, "T_ARRAY");
          expressionsMap.set(possVarMatch.index, "array");
        }
        
        usedTypes.push(possVarMatch[0]);
        if (possVarMatch[0] === "integer") {
          lexemsMap.set(possVarMatch.index, "T_TYPE");
          expressionsMap.set(possVarMatch.index, "integer");
        }
        if (possVarMatch[0] === "byte") {
          lexemsMap.set(possVarMatch.index, "T_TYPE");
          expressionsMap.set(possVarMatch.index, "byte");
        }
        if (possVarMatch[0] === "word") {
          lexemsMap.set(possVarMatch.index, "T_TYPE");
          expressionsMap.set(possVarMatch.index, "word");
        }
        if (possVarMatch[0] === "shortint") {
          lexemsMap.set(possVarMatch.index, "T_TYPE");
          expressionsMap.set(possVarMatch.index, "shortint");
        }
        if (possVarMatch[0] === "longint") {
          lexemsMap.set(possVarMatch.index, "T_TYPE");
          expressionsMap.set(possVarMatch.index, "longint");
        }
        if (possVarMatch[0] === "real") {
          lexemsMap.set(possVarMatch.index, "T_TYPE");
          expressionsMap.set(possVarMatch.index, "real");
        }
        if (possVarMatch[0] === "single") {
          lexemsMap.set(possVarMatch.index, "T_TYPE");
          expressionsMap.set(possVarMatch.index, "single");
          
        }
        if (possVarMatch[0] === "double") {
          lexemsMap.set(possVarMatch.index, "T_TYPE");
          expressionsMap.set(possVarMatch.index, "double");
        }
        if (possVarMatch[0] === "extended") {
          lexemsMap.set(possVarMatch.index, "T_TYPE");
          expressionsMap.set(possVarMatch.index, "extended");
        }
        if (possVarMatch[0] === "boolean") {
          lexemsMap.set(possVarMatch.index, "T_TYPE");
          expressionsMap.set(possVarMatch.index, "boolean");
        }
        if (possVarMatch[0] === "char") {
          lexemsMap.set(possVarMatch.index, "T_TYPE");
          expressionsMap.set(possVarMatch.index, "char");
        }
        if (lexemsMap.get(possVarMatch.index) === undefined)
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
      expressionsMap.set(possVarMatch.index, possVarMatch[0]);
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
    if ([":=", "+=", "-=", "*=", "/="].includes(possSymbMatch[0])){
      lexemsMap.set(possSymbMatch.index, "T_ASSIGNMENT");
      expressionsMap.set(possSymbMatch.index, possSymbMatch[0]);
    }
    if (".." === possSymbMatch[0]){
      lexemsMap.set(possSymbMatch.index, "T_DOUBLE_DOT");
      expressionsMap.set(possSymbMatch.index, possSymbMatch[0]);}
    if ([">>", "<<"].includes(possSymbMatch[0]))
      lexemsMap.set(possSymbMatch.index, "T_SHIFT");
    if (["++", "--"].includes(possSymbMatch[0]))
      lexemsMap.set(possSymbMatch.index, "T_UNARY_OPERATOR");
    if (possSymbMatch[0] === "<=" || possSymbMatch[0] === ">=")
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
      expressionsMap.set(possSymbMatch.index, possSymbMatch[0]);
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

  possSymbMatch = str.match(comparsionRegex);
  while (possSymbMatch !== null) {
    lexemsMap.set(possSymbMatch.index, "T_COMPARSION");
    expressionsMap.set(possSymbMatch.index, possSymbMatch[0]);
    symbols.push(possSymbMatch[0]);
    str = str.replace(possSymbMatch[0], " ");
    possSymbMatch = str.match(comparsionRegex);
  }

  possSymbMatch = str.match(symbolsRegex);
  while (possSymbMatch !== null) {
    // console.log(possSymbMatch);
    symbols.push(possSymbMatch[0]);
    if (possSymbMatch[0] === "(")
      lexemsMap.set(possSymbMatch.index, "T_LEFT_PARENTHESIS");
      expressionsMap.set(possSymbMatch.index, possSymbMatch[0]);
    if (possSymbMatch[0] === ")")
      lexemsMap.set(possSymbMatch.index, "T_RIGHT_PARENTHESIS");
      expressionsMap.set(possSymbMatch.index, possSymbMatch[0]);
    if (possSymbMatch[0] === "[")
      lexemsMap.set(possSymbMatch.index, "T_LEFT_BRACKET");
      expressionsMap.set(possSymbMatch.index, possSymbMatch[0]);
    if (possSymbMatch[0] === "]")
      lexemsMap.set(possSymbMatch.index, "T_RIGHT_BRACKET");
      expressionsMap.set(possSymbMatch.index, possSymbMatch[0]);
    if (possSymbMatch[0] === ":")
      lexemsMap.set(possSymbMatch.index, "T_COLUMN");
      expressionsMap.set(possSymbMatch.index, possSymbMatch[0]);
    if (possSymbMatch[0] === ";")
      lexemsMap.set(possSymbMatch.index, "T_SEMICOLUMN");
      expressionsMap.set(possSymbMatch.index, possSymbMatch[0]);
    if (possSymbMatch[0] === ".")
      lexemsMap.set(possSymbMatch.index, "T_DOT");
      expressionsMap.set(possSymbMatch.index, possSymbMatch[0]);
    if (
      possSymbMatch[0] === "<" ||
      possSymbMatch[0] === ">" ||
      possSymbMatch[0] === "="
    )
      lexemsMap.set(possSymbMatch.index, "T_COMPARSION");
      expressionsMap.set(possSymbMatch.index, possSymbMatch[0]);

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
    expressionsMap.set(possNumbMatch.index, possNumbMatch[0]);
    str = str.replace(possNumbMatch[0], " ".repeat(possNumbMatch[0].length));
    possNumbMatch = str.match(floatRegex);
  }

  possNumbMatch = str.match(integerRegex);
  while (possNumbMatch !== null) {
    integerNumbers.push(possNumbMatch[0]);
    lexemsMap.set(possNumbMatch.index, "T_INTEGER");
    expressionsMap.set(possNumbMatch.index, possNumbMatch[0]);
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
const expressionsSortedMap = new Map(
  [...expressionsMap.entries()].sort((a, b) => a[0] - b[0])
);
const lexemsTable = [...lexemsSortedMap.entries()].map(e => e[1]);
const lexemsIndexes = [...lexemsSortedMap.entries()].map(e => e[0]);
const expressionsTable = [...expressionsSortedMap.entries()].map(e => e[1]);
const expressionsIndexes = [...expressionsSortedMap.entries()].map(e => e[0]);

const onlyBeginEnd = (index) => {
  for(let i= index; i < lexemsTable.length; i++){
    if(lexemsTable[i] === "T_BEGIN" || lexemsTable[i] === undefined){
      console.log('start')
      if(lexemsTable[i+1] === "T_END"){
        if(
          lexemsTable[i+2] === "T_SEMICOLUMN" ||
          (
            lexemsTable[i+2] === "T_DOT" &&
            lexemsTable[i+3] === undefined
          )
          ){
            if(lexemsTable[i+3] === "T_END"){
              return onlyBeginEnd(index+5)
            }
            
        }else{
          throw new Error(`ERROR at ${
            lexemsIndexes[index]
            } 
            You have to place SEMICOLUMN or DOT(it this END is the last) after END \n`)
        }
      }else if(lexemsTable[i + 1] === "T_BEGIN"){
        console.log({i })
        return onlyBeginEnd(index+1)
      }else{
        throw new Error(`ERROR at ${
          lexemsIndexes[index]
          } 
          You haven't declared any variables, so you can use only BEGIN END \n`)
      }
    }else{
      throw new Error(`ERROR at ${
        lexemsIndexes[index]
        } 
        You haven't declared any variables, so you can use only BEGIN here \n`)
    }
  }
}

const checkSyntax = (lexemsTable, index) => {
  let errorOccured = false;

if(!lexemsTable.includes("T_VAR")){
  onlyBeginEnd(0)
}
// const arr = [];
// arr.includes
if (
  lexemsTable[index] === "T_VAR"
){
  if (
    index !== 0 
  ){
    errorOccured = true;
    console.log(
      `ERROR at ${
        lexemsIndexes[index]
      } You can declare variables only at the beginning`
    );
  }else if (
    lexemsTable[index + 1] !== "T_VARIABLE"
  ){
    errorOccured = true;
    console.log(
      `ERROR at ${
        lexemsIndexes[index]
      } You have to declare variables after VAR`
    );
  }else{
    let isThereMoreVariables = true;
    let semiColumnIndex = index; //!it's just to use this var next
    while(isThereMoreVariables){
      semiColumnIndex = addVariablesToTheList(semiColumnIndex + 1);
      isThereMoreVariables = checkVar(semiColumnIndex);
      
    }
    console.log({semiColumnIndex})
  }
}

//! VAR a,b : INTEGER;

  if (
      lexemsTable[lexemsTable.length - 1] !== "T_SEMICOLUMN" &&(
        lexemsTable[lexemsTable.length - 2] !== "T_END" ||
        lexemsTable[lexemsTable.length - 1] !== "T_DOT" )
      
      ) {
    errorOccured = true;
    console.log(
      `ERROR at ${
        lexemsIndexes[lexemsTable.length - 1]
      } You have to place semicolumn at the end`
    );
  }

  if (lexemsTable[index] === "T_VARIABLE") {
    if (
      lexemsTable[index + 1] === "T_IF" ||
      lexemsTable[index + 1] === "T_BEGIN" ||
      lexemsTable[index + 1] === "T_END"
    ) {
      errorOccured = true;
      console.log(
        `ERROR at ${
          lexemsIndexes[index + 1]
        } You can't place it after variable`
      );
    }
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
      (lexemsTable[index - 1] !== "T_TO" &&
        (lexemsTable[index - 1] !== "T_ASSIGNMENT" &&
          (lexemsTable[index - 1] !== "T_LEFT_PARENTHESIS" &&
            lexemsTable[index - 2] !== "T_MATH_OPERATION")))
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
    if (
      lexemsTable[index + 1] === "T_RIGHT_BRACKET" &&
      lexemsTable[index - 1] === "T_VARIABLE"
    ) {
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
      lexemsTable[index - 1] !== "T_RIGHT_BRACKET" &&
      lexemsTable[index - 1] !== "T_ARRAY"
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
      lexemsTable[index + 1] !== "T_RIGHT_PARENTHESIS"&&
      lexemsTable[index + 1] !== "T_OF"
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
      lexemsTable[index - 1] !== "T_LEFT_PARENTHESIS" &&
      lexemsTable[index - 1] !== "T_IF"
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
        lexemsTable[index - 1] !== "T_RIGHT_BRACKET" &&
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
  if (
    lexemsTable[index] === "T_END"
    ) {
    if (
      lexemsTable[index + 1] === "T_DOT" &&
      lexemsTable[index + 2] !== undefined

      ) {
      errorOccured = true;
      console.log(
        `ERROR at ${lexemsIndexes[index]} index: You have to place a semicolumn after not last 'end' `
      );
    }  
    if (
      lexemsTable[index + 1] !== "T_SEMICOLUMN" &&
      lexemsTable[index + 1] !== "T_END" &&
      lexemsTable[index + 1] !== "T_DOT"
       
      ) {
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
      (lexemsTable[index - 1] !== "T_TO" &&
        (lexemsTable[index - 1] !== "T_ASSIGNMENT" &&
          (lexemsTable[index - 1] !== "T_LEFT_PARENTHESIS" &&
            lexemsTable[index - 2] !== "T_MATH_OPERATION")))
    ) {
      errorOccured = true;
      console.log(
        `ERROR at ${
          lexemsIndexes[index + 1]
        } index : You can't use BINARY OPERATOR without ASSIGNMENT OPERATOR before`
      );
    }
  }

  if (lexemsTable[index] === "T_FOR") {
    if (lexemsTable[index + 1] === "T_VARIABLE") {
      if (lexemsTable[index + 2] === "T_ASSIGNMENT") {
        if (
          lexemsTable[index + 3] !== "T_VARIABLE" &&
          lexemsTable[index + 3] !== "T_INTEGER" &&
          lexemsTable[index + 3] !== "T_LEFT_PARENTHESIS"
        ) {
          errorOccured = true;
          console.log(
            `ERROR at ${
              lexemsIndexes[index + 3]
            } index : You can't use ${lexemsTable[index + 3].substring(2,30)} after ASSIGNMENT OPERATOR`
          );
        }
        
        
        // index = index + 3;
        if (lexemsTable[index + 3] === "T_LEFT_PARENTHESIS") {
          index = findParenthesisRightPair(index + 3);
        }else if (
          lexemsTable[index + 3] === "T_VARIABLE" &&
          lexemsTable[index + 4] === "T_LEFT_PARENTHESIS"
        ) {
          index = findParenthesisRightPair(index + 4);
        } else if (
          lexemsTable[index + 3] === "T_VARIABLE" &&
          lexemsTable[index + 4] === "T_LEFT_BRACKET"
        ) {
          index = findBracketRightPair(index + 4);
        } else {
          const toIndex = lexemsTable.indexOf("T_TO", index);
          const contentBetweenForAndTo = checkContentBetweenKeywords(index+3, toIndex, 0);
          if(contentBetweenForAndTo){
            errorOccured = true;
            console.log(contentBetweenForAndTo)
          }
          index = toIndex - 1;
        }


        if (lexemsTable[index + 1] !== "T_TO") {
          console.log(index);
          errorOccured = true;
          console.log(
            `ERROR at ${
              lexemsIndexes[index + 1]
            } index : You have to place 'TO' here`
          );
        } else if (lexemsTable[index + 2] === "T_DO") {
          errorOccured = true;
          console.log(
            `ERROR at ${
              lexemsIndexes[index + 2]
            } index : You have to define the end of the range after 'TO' here`
          );
        } else if (lexemsTable[index + 2] === "T_TO") {
          errorOccured = true;
          console.log(
            `ERROR at ${
              lexemsIndexes[index + 2]
            } index : You can't place another 'TO' after 'TO' here`
          );
        }else{
          const doIndex = lexemsTable.indexOf("T_DO", index + 1);
          
          const contentBetweenToAndDo = checkContentBetweenKeywords(index+2, doIndex, 1);
          if(contentBetweenToAndDo){
            errorOccured = true;
            console.log(contentBetweenToAndDo)
          }
          if (lexemsTable[doIndex+1] === "T_SEMICOLUMN") {
            console.log(`object`)
            errorOccured = true;
            console.log(
              `ERROR at ${lexemsIndexes[doIndex+1]} index : You can't place ";" here`
            );
          }
          if (lexemsTable[doIndex+1] === "T_BEGIN") {
            if (lexemsTable[doIndex+2] === "T_SEMICOLUMN") {
              console.log(`object`)
              errorOccured = true;
              console.log(
                `ERROR at ${lexemsIndexes[doIndex+2]} index : You can't place ";" here`
              );
            }
          }
          if(doIndex !== -1){
            // if (lexemsTable[doIndex + 1] !== "T_BEGIN") {
            //   errorOccured = true;
            //   console.log(
            //     `ERROR at ${
            //       lexemsIndexes[doIndex + 1]
            //     } index : You have to place "BEGIN" after 'DO'`
            //   ); 
            // } 
          } else{
            errorOccured = true;
              console.log(
                `ERROR at ${
                  lexemsIndexes[index + 1]
                } index : You have to place "DO" after "TO"`
              );
          }

          // index = lexemsIndexes[lexemsTable.indexOf("T_DO", index + 1)];
          
          index = doIndex+2
          // else if (
          //   lexemsTable[index + 2] !== "T_VARIABLE" &&
          //   lexemsTable[index + 2] !== "T_INTEGER" &&
          //   lexemsTable[index + 2] !== "T_FLOAT" &&
          //   lexemsTable[index + 2] !== "T_LEFT_PARENTHESIS"
          // ) {
          //   console.log(`object`);
          // }
        
          // console.log(`doIndex ${doIndex}`);
          // index += 2;
          // console.log(index)
        }
      }else{
        errorOccured = true;
        console.log(
          `ERROR at ${lexemsIndexes[index + 2]} index : You have to initialize iterator's value here`
        );
      }
    }else{
      errorOccured = true;
      console.log(
        `ERROR at ${lexemsIndexes[index + 1]} index : You have to place iterator here`
      );
    }
  }
  if (lexemsTable[index] === "T_THEN") {
    errorOccured = true;
    console.log(
      `ERROR at ${lexemsIndexes[index]} index : You can't place 'THEN' here`
    );
  }

  if(lexemsTable[index] === "T_IF"){
    ifAmount++;
    if (lexemsTable[index + 1] === "T_IF"){
      errorOccured = true;
      console.log(
        `ERROR at ${lexemsIndexes[index+1]} index : You can't place another 'IF' here`
      );
    }
    const thenIndex = lexemsTable.indexOf("T_THEN", index);
    if(thenIndex === -1 ){
      errorOccured = true;
      console.log(
        `ERROR at ${lexemsIndexes[index+1]} index : Expected 'THEN'`
      );
    }
    if (lexemsTable[thenIndex + 1] === "T_SEMICOLUMN"){
      errorOccured = true;
      console.log(
        `ERROR at ${lexemsIndexes[thenIndex+1]} index : You can't place ; after then`
      );
    }
    // console.log(thenIndex)
    // console.log(index)
    if(thenIndex - index === 1 ){
      errorOccured = true;
      console.log(
        `ERROR at ${lexemsIndexes[index+1]} index : You have to write your condition`
      );
    }
    if(lexemsTable[thenIndex - 1] === "T_SEMICOLUMN"){
      errorOccured = true;
      console.log(
        `ERROR at ${lexemsIndexes[index+1]} index : Expected 'THEN' got ';'`
      );
    }
    if(lexemsTable[thenIndex + 1] === "T_END"){
      errorOccured = true;
      console.log(
        `ERROR at ${lexemsIndexes[thenIndex+1]} index : Expected statement after 'THEN' got 'END'`
      );
    }
    const contentBetweenIfAndThen = checkContentBetweenKeywords(index+1, thenIndex, 2);
      // index = rightPr;
      if(contentBetweenIfAndThen){
        errorOccured = true;
        console.log(contentBetweenIfAndThen)
      }
    // if(lexemsTable[index + 1] === "T_LEFT_PARENTHESIS"){
    //   const rightPr = findParenthesisRightPair(index + 1);
    //   const contentBetweenIfAndThen = checkContentBetweenKeywords(index+1, rightPr, 2);
    //   index = rightPr;
    //   if(contentBetweenIfAndThen){
    //     errorOccured = true;
    //     console.log(contentBetweenIfAndThen)
    //   }
    //   const thenIndex = lexemsTable.indexOf("T_THEN", index + 1);
    //   if(lexemsTable[index + 1] === "T_THEN"){
    //     // if(lexemsTable[index + 2] === "T_BEGIN"){
    //     //   index+=2
    //     // }else{
    //     //   errorOccured = true;
    //     //   console.log(
    //     //     `ERROR at ${lexemsIndexes[index+2]} index : You have to place 'BEGIN' here`
    //     //   );
    //     // }
    //   }else{
    //     errorOccured = true;
    //     console.log(
    //       `ERROR at ${lexemsIndexes[index+1]} index : You have to place 'THEN' here`
    //     );
    //   }
    // }
    // else if (lexemsTable[index + 1] === "T_IF"){
    //   errorOccured = true;
    //   console.log(
    //     `ERROR at ${lexemsIndexes[index+1]} index : You can't place another 'IF' here`
    //   );
    // }
    // else{
    //   errorOccured = true;
    //   console.log(
    //     `ERROR at ${lexemsIndexes[index+1]} index : You have to wrap your condition in parenthesis`
    //   );
    // }
    //! Check what's between if and then
    //? how to check if else is after the right end
    index = thenIndex
  }

  if (lexemsTable[index] === "T_ELSE") {
    if (ifAmount > 0) {
      
    }else{
      errorOccured = true;
      console.log(
        `ERROR at ${lexemsIndexes[index]} index : You have to use 'IF' before 'ELSE'`
      );
    }
    if (lexemsTable[index - 1] !== "T_END") {
      errorOccured = true;
      console.log(
        `ERROR at ${lexemsIndexes[index]} index : You have to use 'ELSE' after 'END'`
      );
    }

    const closestIf = findClosestLeftIf(index);
    const closestThen = findClosestThen(closestIf);
    const closestBegin = closestThen + 1;
    const correspondingEnd = findEnd(closestBegin);
    // console.log(`------------`)
    // console.log(closestIf);
    // console.log(closestThen);
    // console.log(closestBegin);
    // console.log(correspondingEnd);
    // console.log(`------------`)
    if (index - 1 !== correspondingEnd){
      errorOccured = true;
      console.log(
        `ERROR at ${lexemsIndexes[index]} index : You have to use 'ELSE' after 'IF' construction`
      );
    }

    
    if (lexemsTable[index + 1] !== "T_BEGIN") {
      errorOccured = true;
      console.log(
        `ERROR at ${lexemsIndexes[index]} index : You have to open new logic statement after 'ELSE'`
      );
    }
  }

  
  if (lexemsTable[index] === "T_TO") {
    console.log({index})
    errorOccured = true;
    console.log(
      `ERROR at ${lexemsIndexes[index]} index : You can't place 'TO' here`
    );
  }
  if (lexemsTable[index] === "T_BEGIN") {
    // console.log(`object`)
    // console.log(lexemsTable[index+1])
    if (lexemsTable[index+1] === "T_SEMICOLUMN") {
      console.log(`object`)
      errorOccured = true;
      console.log(
        `ERROR at ${lexemsIndexes[index+1]} index : You can't place ";" here`
      );
    }
    
  }
  if (lexemsTable[index] === "T_DO") {
    errorOccured = true;
    console.log(
      `ERROR at ${lexemsIndexes[index]} index : You can't place 'DO' here`
    );
  }
  // if (lexemsTable[index] === "T_BEGIN") {
  //   errorOccured = true;
  //   console.log(
  //     `ERROR at ${lexemsIndexes[index]} index : You can't place 'BEGIN' here`
  //   );
  // }
  if (!errorOccured && index <= lexemsTable.length) {
    // console.log(index);
    // console.log("Moving on");
    checkSyntax(lexemsTable, index + 1);
  }
  if (!errorOccured && index > lexemsTable.length) {
    console.log(`\n~~~~~~~~~~Anylize completed successfully~~~~~~~~~~`);
    buildTree();
  }
};

const buildTree = () => {
  let tabs = 0
  
    for(let i= 0; i < lexemsTable.length; i++){
      if(
        lexemsTable[i] == "T_ELSE" ||
        lexemsTable[i] == "T_FOR" ||
        lexemsTable[i] == "T_THEN" ||
        lexemsTable[i] == "T_IF" 
      ){
        console.log(`${" ".repeat(tabs*4)} ${lexemsTable[i]}`)
        tabs++;
      }
    
  }
}

const findClosestLeftIf = start => {
  let if_else_pairs = 1;
  for(let i = start + 1; i > 0; i--){
    if(lexemsTable[i] === "T_ELSE"){
      if_else_pairs++
    }
    if(lexemsTable[i] === "T_IF"){
      if(if_else_pairs !== 0){
        if_else_pairs--
      }else{
        return i
      }
    }
  }
  return 0
}

const findClosestThen = start => {
  for(let i = start; i < lexemsTable.length; i++){
    if(lexemsTable[i] === "T_THEN"){
      return i
    }
  }
  return 0
}



//!  find closest left if
//!  take closest begin after T_THEN
//!  find corresponding T_END and only after that should be our else

const checkContentBetweenKeywords = (start, end, mode=0) => {
  let keyword1 = 'FOR'
  let keyword2 = 'TO'
  if(mode === 1){
    keyword1 = 'TO'
    keyword2 = 'DO'
  }else if(mode === 2){
    keyword1 = 'IF'
    keyword2 = 'THEN'
  }
  if(lexemsTable[start] === "T_LEFT_PARENTHESIS"){
    const rightPr = findParenthesisRightPair(start);
    if (rightPr > end){
      // return "ERROR"
      return `Incorrectly placed parenthesis at ${lexemsIndexes[rightPr]}`;
    }
    else{
      return checkContentBetweenKeywords(start+1, rightPr)
    } 
  }else{
    for (let i = start; i < end; i++) {
      if (
        lexemsTable[i] === "T_ASSIGNMENT" ||
        lexemsTable[i] === "T_SYMBOL" ||
        lexemsTable[i] === "T_COLUMN" ||
        lexemsTable[i] === "T_SEMICOLUMN"
      ) {
        return `
        ERROR at index ${lexemsIndexes[i]} : Prohibited symbols between ${keyword1}  and ${keyword2}
        `;
      }
    }
  }
  return 0
}

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

findEnd = index => {
  let pairs = 1;
  let beginInd = index;
  let endInd = 0;
  for (let i = beginInd + 1; i < lexemsTable.length; i++) {
    if (lexemsTable[i] === "T_BEGIN") {
      pairs++;
      // if (prPairs === 1) leftPr = i;
    }
    if (lexemsTable[i] === "T_END") {
      if (pairs === 1) {
        endInd = i;
        break;
      } else if (pairs > 1) pairs--;
    }
  }
  return endInd;
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

findType = ( ) => {
  
}

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

const addVariablesToTheList = (index) => {
  const columnIndex = lexemsTable.indexOf("T_COLUMN", index);
  if(columnIndex === -1){
    throw new Error(`
        \nError at index ${index}, wrong variable declaration \n
        Maybe you wanted to place "BEGIN" here?
        \n
        \n
      `)
  }
  const temporaryVault = [];
  let semiColumnIndex = 0;
  for(let i = index; i < columnIndex; i++){
    if(validVariables.includes(expressionsTable[i])){
      console.log({i}, expressionsTable[i]);
      temporaryVault.push(expressionsTable[i])
    }else if(
      expressionsTable[i] === "," &&
      lexemsTable[i + 1] !== "T_VARIABLE"
      ){
      throw new Error(`
        \nError at index ${expressionsIndexes[i]}, you can't use "COMMA" here \n\n
      `)
    }else if(expressionsTable[i] !== ","){
      throw new Error(`
        \nError at index ${expressionsIndexes[i]}, you can't use "${expressionsTable[i]}" as a variable \n\n
      `)
    }
    
  }
  console.log({columnIndex})
  if(
    lexemsTable[columnIndex+1] !== "T_TYPE" &&
    lexemsTable[columnIndex+1] !== "T_ARRAY"
  ){
    throw new Error(`
      \nError at index ${expressionsIndexes[columnIndex+1]}, you have to define TYPE here \n\n
    `)
  }
  if(expressionsTable[columnIndex+1] === "array"){
    if(
      expressionsTable[columnIndex+2] === "[" &&
      lexemsTable[columnIndex+3] === "T_INTEGER" &&
      lexemsTable[columnIndex+4] === "T_DOUBLE_DOT" &&
      lexemsTable[columnIndex+5] === "T_INTEGER" &&
      expressionsTable[columnIndex+6] === "]"
      ){
        if(
          lexemsTable[columnIndex+7] === "T_OF" &&
          lexemsTable[columnIndex+8] === "T_TYPE" &&
          lexemsTable[columnIndex+9] === "T_SEMICOLUMN"){
            semiColumnIndex = columnIndex + 9;
            temporaryVault.forEach(e => {
              if(declaredVariables[e] === undefined){
                declaredVariables[e] = {
                        "name" : e, 
                        "class":"array",
                        "type" :`${expressionsTable[columnIndex+8]}`,
                        "length" : +expressionsTable[columnIndex+5],
                        // "length" : (expressionsTable[columnIndex+5].toString()).parseInt(),
                        "value": Array(+expressionsTable[columnIndex+5])
                        } 
                    }else{
                      throw new Error(`
                      \nError, variable "${e}" has already been declared \n\n
                    `)
                    }
            })
        }
        else{
          throw new Error(`
          \nError at index ${expressionsIndexes[columnIndex+7]}, you have to define TYPE of the ARRAY correctly \n\n
        `)
        }
    }
    else{
      throw new Error(`
      \nError at index ${expressionsIndexes[columnIndex+2]}, you have to define ARRAY correctly \n\n
    `)
    }
  }else{
    if(lexemsTable[columnIndex+2] === "T_SEMICOLUMN"){
      semiColumnIndex = columnIndex+2;
      temporaryVault.forEach(e => { 
        if(declaredVariables[e] === undefined){
        declaredVariables[e] = {
                "name" : e, 
                "class":"variable",
                "type" :`${expressionsTable[columnIndex+1]}`,
                "value":undefined
                }
        }
      })
    }
    else{
      throw new Error(`
      \nError at index ${expressionsIndexes[columnIndex+2]}, you have to place ";" after TYPE \n\n
    `)
    }
  }
  console.log(declaredVariables)
  console.log({semiColumnIndex})
  return semiColumnIndex;
}

const checkVar = (semiColumnIndex) => {
  if(lexemsTable[semiColumnIndex + 1] === "T_BEGIN"){
    return false
  }else if (lexemsTable[semiColumnIndex + 1] === "T_VARIABLE"){
    return true
  }else{
    throw new Error(`
    \nError at index ${expressionsIndexes[semiColumnIndex+1]}, you have to start you program with "BEGIN" clause\n\n
  `)
  }
}
console.log(" \nComment strings : ");
console.log(comments);
console.log(` \nValid variables : `);
console.log(validVariables);
console.log(` \nInvalid variables : `);
console.log(invalidVariables);
console.log(` \nReserved keywords :  `);
console.log(reservedWords);
console.log(` \nUsed symbols : `);
console.log(symbols);
console.log(` \nUsed ariph. operands : `);
console.log(ariphmeticOperandsArr);
console.log(` \nUsed prohibited symbols : `);
console.log(prohibitedSymbolsArr);
console.log(` \nReal : `);
console.log(realNumbers);
console.log(` \nInteger : `);
console.log(integerNumbers);
console.log(lexemsSortedMap);
console.log(lexemsTable);
console.log(expressionsSortedMap);

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
