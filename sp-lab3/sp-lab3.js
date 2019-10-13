const expression = `case c begin 0: b:=2*a[n]; else: b:=d end 5sraka (*2asbddas*) function b1() begin
do smth;
end;
`;
const invalidVariables = [];
const words = `and array begin case const div do downto else end file for function goto if in label mod nil not of or packed procedure program record repeat set then to type until var while with integer char real string boolean array file set record enumerated subrange`;
const reservedWordsList = words.split(" ");
const comments = [];
const validVariables = [];
const reservedWords = [];
const symbols = [];
const numbers = [];

const doubleSymbols = /(:=)|(\+=)|(-=)/;
const symbolsRegex = /[\,\.\;\:\(\)\[\]\-\-\<\>\*\/]/;
const varRegex = /[A-Za-z]+[0-9_]*[A-Za*z]*/;
const numberRegex = /\d+|(\d+)(\.\d+)(e(\+|-)?(\d+))?|(\d+)(\.\d+)e(\+|-)?|(\d+)e(\+|-)?|(\d+)(e(\+|-)?(\d+))?/;
const commentsRegex = /(\/\/.*\n?)|\(\*(.|\n)*?\*\)|\{(.|\n)*?\}/;
const invRegex = /\d+[A-Za-z]+/;

// const regx = /\d+[A-Za-z\,\.\;\:\(\)\[\]\+\+=\:=\-\-=\<\>\*\/]+/; //! Locates a word starting with a digit
// const regx1 = /[\,\.\;\:\{\}\(\)\[\]\+\+=\:=\-\-=\<\>\*\/]+[A-Za-z\,\.\;\:\{\}\(\)\[\]\+\+=\:=\-\-=\<\>\*\/]*/; //!Locates a word that starts with an invalid symbol
// const regx2 = /[A-Za-z]+[0-9\,\.\d;\:\{\}\(\)\[\]\+\+=\:=\-\-=\<\>\*\/]+[0-9A-Za-z\,\.\;\:\{\}\(\)\[\]\+\+=\:=\-\-=\<\>\*\/]*/; //! Locates a word starting with a letter and containing invalid symbols
findComments = str => {
  let lastMatch = str.match(commentsRegex);
  while (lastMatch !== null) {
    comments.push(lastMatch[0]);
    str = str.replace(lastMatch[0], "");
    lastMatch = str.match(commentsRegex);
  }
  return str;
};

findInvalidVariables = str => {
  let lastMatch = str.match(invRegex);
  while (lastMatch !== null) {
    invalidVariables.push(lastMatch[0]);
    str = str.replace(lastMatch[0], " ");
    lastMatch = str.match(invRegex);
  }
  return str;
};

findValidVariablesAndReservedWords = str => {
  let possVarMatch = str.match(varRegex);
  while (possVarMatch !== null) {
    let flagReserved = false;
    for (const reswordIndex in reservedWordsList) {
      if (possVarMatch[0] === reservedWordsList[reswordIndex]) {
        reservedWords.push(possVarMatch[0]);
        str = str.replace(possVarMatch[0], " ");
        possVarMatch = str.match(varRegex);
        flagReserved = true;
        break;
      }
    }
    if (!flagReserved) {
      validVariables.push(possVarMatch[0]);
      str = str.replace(possVarMatch[0], " ");
      possVarMatch = str.match(varRegex);
    }
  }

  return str;
};

findSymbols = str => {
  let possSymbMatch = str.match(doubleSymbols);
  while (possSymbMatch !== null) {
    symbols.push(possSymbMatch[0]);
    str = str.replace(possSymbMatch[0], " ");
    possSymbMatch = str.match(doubleSymbols);
  }

  possSymbMatch = str.match(symbolsRegex);
  while (possSymbMatch !== null) {
    symbols.push(possSymbMatch[0]);
    str = str.replace(possSymbMatch[0], " ");
    possSymbMatch = str.match(symbolsRegex);
  }
  return str;
};

findNumbers = str => {
  let possNumbMatch = str.match(numberRegex);
  while (possNumbMatch !== null) {
    numbers.push(possNumbMatch[0]);
    str = str.replace(possNumbMatch[0], " ");
    possNumbMatch = str.match(numberRegex);
  }

  return str;
};
const withoutComments = findComments(expression);
const withoutInvalidVariables = findInvalidVariables(withoutComments);
const withoutVariablesAndReservedWords = findValidVariablesAndReservedWords(
  withoutInvalidVariables
);
const withoutSymbols = findSymbols(withoutVariablesAndReservedWords);
const withoutNumbers = findNumbers(withoutSymbols);

console.log(" \nComment strings : ");
console.log(comments);
console.log(` \nValid variables : `);
console.log(validVariables);
console.log(` \nInvalid variables : `);
console.log(invalidVariables);
console.log(` \nReservew keywords :  `);
console.log(reservedWords);
console.log(` \nUsed symbols : `);
console.log(symbols);
console.log(` \nDigits : `);
console.log(numbers);
