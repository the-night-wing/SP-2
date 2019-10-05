const str = "switch (c) {case 1:console.trace(c); break; }";

const reservedWords = [];
// reservedWords.findIndex(val);

class A {
  run(string) {
    let withoutSemiColumn = string.split(";");
    let withoutSpaces = [];
    withoutSemiColumn.forEach((e, i) => {
      withoutSpaces[i] = e.trim();
    });
    withoutSpaces.forEach(el => {
      if (el === "{") console.log("opening bracket");
      if (el === "}") console.log("closing bracket");
    });
    console.log(withoutSpaces);
    // console.log(sp);
  }
}

const a = new A();

a.run(str);
