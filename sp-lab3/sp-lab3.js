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
// const numberRegex = /\d+\.*\d* /;
const numberRegex = /\d+|(\d+)(\.\d+)(e(\+|-)?(\d+))?|(\d+)(\.\d+)e(\+|-)?|(\d+)e(\+|-)?|(\d+)(e(\+|-)?(\d+))?/;
const commentsRegex = /(\/\/.*\n?)|\(\*(.|\n)*?\*\)|\{(.|\n)*?\}/;
const invRegex = /\d+[A-Za-z]+/;

const analyse = expression => {
  let exprCopy = expression;
  ///TODO Get rid of invalid identifiers;
  //TODO extract symbols
  //TODO locate valid indentifiers;
  //TODO find reserved words
  const regx = /\d+[A-Za-z\,\.\;\:\(\)\[\]\+\+=\:=\-\-=\<\>\*\/]+/; //! Locates a word starting with a digit
  const regx1 = /[\,\.\;\:\{\}\(\)\[\]\+\+=\:=\-\-=\<\>\*\/]+[A-Za-z\,\.\;\:\{\}\(\)\[\]\+\+=\:=\-\-=\<\>\*\/]*/; //!Locates a word that starts with an invalid symbol
  const regx2 = /[A-Za-z]+[0-9\,\.\d;\:\{\}\(\)\[\]\+\+=\:=\-\-=\<\>\*\/]+[0-9A-Za-z\,\.\;\:\{\}\(\)\[\]\+\+=\:=\-\-=\<\>\*\/]*/; //! Locates a word starting with a letter and containing invalid symbols
  const invRegex = /\d+[A-Za-z]+/;
  // /[\,\.\;\:\{\}\(\)\[\]\+\+=\:=\-\-=\<\>\*\/]+[A-Za-z\,\.\;\:\{\}\(\)\[\]\+\+=\:=\-\-=\<\>\*\/]*/,
  // /[A-Za-z]+[0-9\,\.\d;\:\{\}\(\)\[\]\+\+=\:=\-\-=\<\>\*\/]+[0-9A-Za-z\,\.\;\:\{\}\(\)\[\]\+\+=\:=\-\-=\<\>\*\/]*/
  //   console.log(invalidVariables);

  // let possDigitMatch =

  return exprCopy;
};

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
  // console.log(str);
  let lastMatch = str.match(invRegex);
  // console.log(lastMatch);
  while (lastMatch !== null) {
    invalidVariables.push(lastMatch[0]);
    str = str.replace(lastMatch[0], " ");
    lastMatch = str.match(invRegex);
    // console.log(lastMatch);
  }
  return str;
};

findValidVariablesAndReservedWords = str => {
  let possVarMatch = str.match(varRegex);
  console.log(possVarMatch[0]);
  while (possVarMatch !== null) {
    let flagReserved = false;
    for (const reswordIndex in reservedWordsList) {
      if (possVarMatch[0] === reservedWordsList[reswordIndex]) {
        console.log("reserved");
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
  console.log(possSymbMatch);
  while (possSymbMatch !== null) {
    symbols.push(possSymbMatch[0]);
    str = str.replace(possSymbMatch[0], " ");
    possSymbMatch = str.match(doubleSymbols);
  }

  possSymbMatch = str.match(symbolsRegex);
  console.log(possSymbMatch);
  while (possSymbMatch !== null) {
    symbols.push(possSymbMatch[0]);
    str = str.replace(possSymbMatch[0], " ");
    possSymbMatch = str.match(symbolsRegex);
  }

  return str;
};

findNumbers = str => {
  let possNumbMatch = str.match(numberRegex);
  // console.log(possNumbMatch);
  while (possNumbMatch !== null) {
    numbers.push(possNumbMatch[0]);
    str = str.replace(possNumbMatch[0], " ");
    possNumbMatch = str.match(numberRegex);
  }

  return str;
};
// \(+=)\(:=)\-=
const withoutComments = findComments(expression);
const withoutInvalidVariables = findInvalidVariables(withoutComments);
const withoutVariablesAndReservedWords = findValidVariablesAndReservedWords(
  withoutInvalidVariables
);
const withoutSymbols = findSymbols(withoutVariablesAndReservedWords);
const withoutNumbers = findNumbers(withoutSymbols);
// console.log(analyse(expression));
console.log(withoutComments);
console.log(withoutInvalidVariables);
console.log(withoutVariablesAndReservedWords);
console.log(withoutSymbols);
console.log(withoutNumbers);
console.log(validVariables);
console.log(invalidVariables);
console.log(reservedWords);
console.log(symbols);
console.log(comments);
console.log(numbers);
