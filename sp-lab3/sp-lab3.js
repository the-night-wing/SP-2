const expression = "case c begin 0: b:=2*a[n]; else: b:=d end 2asbddas";
const invalidVariables = [];
const words = `and array begin case const div do downto else end file for function goto if in label mod nil not of or packed procedure program record repeat set then to type until var while with integer char real string boolean array file set record enumerated subrange`;
const reservedWordsList = words.split(" ");
const validVariables = [];
const reservedWords = [];

const analyse = expression => {
  let exprCopy = expression;
  ///TODO Get rid of invalid identifiers;
  //TODO extract symbols
  //TODO locate valid indentifiers;
  //TODO find reserved words
  const regx = /\d+[A-Za-z\,\.\;\:\{\}\(\)\[\]\+\+=\:=\-\-=\<\>\*\/]+/; //! Locates a word starting with a digit
  const regx1 = /[\,\.\;\:\{\}\(\)\[\]\+\+=\:=\-\-=\<\>\*\/]+[A-Za-z\,\.\;\:\{\}\(\)\[\]\+\+=\:=\-\-=\<\>\*\/]*/; //!Locates a word that starts with an invalid symbol
  const regx2 = /[A-Za-z]+[0-9\,\.\d;\:\{\}\(\)\[\]\+\+=\:=\-\-=\<\>\*\/]+[0-9A-Za-z\,\.\;\:\{\}\(\)\[\]\+\+=\:=\-\-=\<\>\*\/]*/; //! Locates a word starting with a letter and containing invalid symbols
  const invRegex = [
    /\d+[A-Za-z]+/
    // /[\,\.\;\:\{\}\(\)\[\]\+\+=\:=\-\-=\<\>\*\/]+[A-Za-z\,\.\;\:\{\}\(\)\[\]\+\+=\:=\-\-=\<\>\*\/]*/,
    // /[A-Za-z]+[0-9\,\.\d;\:\{\}\(\)\[\]\+\+=\:=\-\-=\<\>\*\/]+[0-9A-Za-z\,\.\;\:\{\}\(\)\[\]\+\+=\:=\-\-=\<\>\*\/]*/
  ];
  const symbolsRegex = / [\,\.\;\:\{\}\(\)\[\]\+=\:=\-=\-\-\<\>\*\/]+ /;
  const varRegex = /[A-Za-z]+[0-9_]*[A-Za*z]*/;
  for (let i = 0; i < invRegex.length; i++) {
    let lastMatch = exprCopy.match(invRegex[i]);
    console.log(lastMatch[0]);
    if (lastMatch !== null) {
      invalidVariables.push(lastMatch[0]);
      exprCopy = expression.replace(lastMatch[0], " ");
    }
  }
  //   console.log(invalidVariables);

  let possVarMatch = exprCopy.match(varRegex);
  console.log(possVarMatch[0]);
  while (possVarMatch !== null) {
    let flagReserved = false;
    for (const reswordIndex in reservedWordsList) {
      if (possVarMatch[0] === reservedWordsList[reswordIndex]) {
        console.log("reserved");
        reservedWords.push(possVarMatch[0]);
        exprCopy = exprCopy.replace(possVarMatch[0], " ");
        possVarMatch = exprCopy.match(varRegex);
        flagReserved = true;
        break;
      }
    }
    if (!flagReserved) {
      validVariables.push(possVarMatch[0]);
      exprCopy = exprCopy.replace(possVarMatch[0], " ");
      possVarMatch = exprCopy.match(varRegex);
    }
  }

  return exprCopy;
};

console.log(analyse(expression));
console.log(validVariables);
console.log(invalidVariables);
console.log(reservedWords);
