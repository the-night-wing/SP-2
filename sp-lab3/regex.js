let stringMatch = `case c begin 0: b:=2*a[n]; else: b:=d end 2asbddas 5.6534;  15.5: .5 0.55 5 //mmmasfs

asd} `;
const regeexp = /\d+\.\d+/;
const regx = /\d+[A-Za-z]+/;
const varRegex = /[A-Za-z][A-Za-z0-9_]*/;
const commentRegex = /\/\/.*\n?/;
const comment2Regex = /\(\*(.|\n)*?\*\)/m;
const comment3Regex = /\{(.|\n)*?\}/m;
const floatRegex = /(\d+)(\.\d+)(e(\+|-)?(\d+))?|(\d+)(\.\d+)e(\+|-)?|(\d+)e(\+|-)?|(\d+)(e(\+|-)?(\d+))? /;
// const comment3Regex = /\{[.]*\}/m;
// const regx = /\d+[A-Za-z\,\.\;\:\{\}\(\)\[\]\+\+=\:=\-\-=\<\>\*\/]+/; //! Locates a word starting with a digit
const regx1 = /[\,\.\;\:\(\)\[\]\+\+=\:=\-\-=\<\>\*\/]+[A-Za-z\,\.\;\:\(\)\[\]\+\+=\:=\-\-=\<\>\*\/]+/; //!Locates a word that starts with an invalid symbol
const regx2 = /[A-Za-z]+[0-9\,\.\d;\:\(\)\[\]\+\+=\:=\-\-=\<\>\*\/]+[0-9A-Za-z\,\.\;\:\(\)\[\]\+\+=\:=\-\-=\<\>\*\/]*/; //! Locates a word starting with a letter and containing invalid symbols
// const numberRegex = /[0-9]+\.*\d* /;
const commentsRegex = /(\/\/.*\n?)|\(\*(.|\n)*?\*\)|\{(.|\n)*?\}/;
const numberRegex = /\d+\.\d+/;

// console.log(stringMatch.match(regx));
// console.log(stringMatch.match(varRegex));
// console.log(stringMatch.match(numberRegex));
console.log(stringMatch.match(numberRegex));
// \d
// stringMatch = stringMatch.replace("begin", "zalupa");
// console.log(stringMatch);

// const str1 = "case c begin 0: b:=2*a[n]; else: b:=d end";
// const str2 = "function(s){}";
// const str3 = "a = b";

// let words = `and array begin case const div do downto else end file for function goto if in label mod nil not of or packed procedure program record repeat set then to type until var while with integer char real string boolean array file set record enumerated subrange`;
// const reservedWordsList = words.split(" ");
// console.log(reservedWordsList);
// const dividingSymbols = ", . ; : { } ( ) [ ] + += := - -= < > * / |";

// class A {
//   analyse(str) {
//     let literal = "";
//     let lastIndex = 0;
//     const divided = str.split("");
//     while (lastIndex < divided.length) {
//       for (lastIndex; lastIndex < divided.length; lastIndex++) {
//         if (
//           !dividingSymbols.includes(divided[lastIndex]) &&
//           divided[lastIndex] !== " "
//         ) {
//           literal += divided[lastIndex];
//         } else {
//           if (literal.length !== 0) {
//             if (typeof reservedWordsMap.get(literal) !== "undefined") {
//               console.log(`${literal} => ${reservedWordsMap.get(literal)}`);
//             } else console.log(`${literal} is a variable`);
//             literal = "";
//           } else if ((divided[lastIndex] = " ")) lastIndex++;
//           else if (
//             typeof dividingSymbolsMap.get(divided[lastIndex]) !== "undefined"
//           ) {
//             console.log(
//               `${divided[lastIndex]} => ${dividingSymbolsMap.get(
//                 divided[lastIndex]
//               )}`
//             );
//           }
//           // lastIndex = i;
//           break;
//         }
//       }
//     }

//     // console.log(literal);
//     // console.log(lastIndex);
//   }

//   run(string) {
//     const bySpaces = [];
//     const bySemiColumn = string.split(";");
//     bySemiColumn.forEach((el, i) => {
//       bySpaces[i] = el.split("");
//     });
//     console.log(bySpaces);
//     let withoutSpaces = [];
//     bySemiColumn.forEach((e, i) => {
//       withoutSpaces[i] = e.trim();
//     });
//     withoutSpaces.forEach(el => {
//       // if (el === "{") console.log("opening bracket");
//       // if (el === "}") console.log("closing bracket");
//     });
//     console.log(withoutSpaces);
//     // console.log(sp);
//   }
// }

// const a = new A();

// // a.run(str1);
// a.analyse(str1);

// const reservedWordsJS = [
//   "arguments",
//   "await",
//   "break",
//   "case",
//   "catch",
//   "class",
//   "const",
//   "continue",
//   "debugger",
//   "default",
//   "delete",
//   "do",
//   "else",
//   "enum",
//   "eval",
//   "export",
//   "extends",
//   "false",
//   "finally",
//   "for",
//   "function",
//   "if",
//   "implements",
//   "import",
//   "in",
//   "instanceof",
//   "interface",
//   "let",
//   "new",
//   "null",
//   "package",
//   "private",
//   "protected",
//   "public",
//   "return",
//   "static",
//   "super",
//   "switch",
//   "this",
//   "throw",
//   "true",
//   "try",
//   "typeof",
//   "var",
//   "void",
//   "while",
//   "with",
//   "yield"
// ];
