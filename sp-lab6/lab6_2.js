const fs = require("fs");

let data;
// let data = "program newprog;";

// const expression = " var a, b n : byte; begin a:=15*10; end.";

// data += expression;

// fs.writeFile("expr.pas", data, err => {
//   if (err) console.log(err);
//   console.log("Successfully Written to File.");
// });

// const nrc = require("node-run-cmd");
// nrc.run("fpc.exe expr.pas > new.txt");

// require("child_process").exec("cmd /c fpc.exe expr.pas > new.txt");

fs.readFile("new.txt", function(err, buf) {
  // console.log(buf.toString());
  data = buf.toString();
  //   console.log(data);
  console.log("``````````````````````````````````````````````````````````");
  console.log(`
  \n
  \n
  \n`);
  let areThereErrors = data.indexOf("Error");
  let newdata = data.split("\n");
  newdata.splice(0, 4);
  newdata.reverse();
  newdata.splice(0, 3);
  newdata.reverse();
  newdata.forEach((el, i) => {
    newdata[i] = el.substring(15, el.length);
  });
  let clear = newdata;
  newdata.forEach((el, i) => {
    if (el.substring(0, 7) === "Warning") {
      newdata[i] = "";
    }
  });
  data = newdata.join("\n");
  data.toLowerCase();
  if (areThereErrors === -1) {
    console.log(`
        \n\n\n
        No errors
        \n\n\n`);
  } else {
    data = data.replace(
      "Identifier not found",
      "You haven't declared this variable :"
    );
    data = data.replace(
      "Identifier not found",
      "You haven't declared this variable :"
    );
    // data = data.replace("Error: There", "You've declared this variable twice");
    data = data.replace(
      "Duplicate identifier",
      "You've declared this variable twice"
    );
    data = data.replace("There were", "");
    data = data.replace("but", "");
    data = data.replace("errors compiling module, stopping", "");
    data = data.replace("Fatal", "Error");
    data = data.replace("Fatal", "Error");
    data = data.replace("Syntax error,", "");
    data = data.replace("Syntax error,", "");
    data = data.replace('"identifier"', "Variable");
    data = data.replace('"identifier"', "Variable");
    data = data.replace("found", "got");
    data = data.replace("found", "got");
    data = data.replace("SmallInt", "shortint");
    data = data.replace("SmallInt", "shortint");
    data = data.replace("expected", "should be here, but found");
    data = data.replace("expected", "should be here, but found");
    data = data.replace("Illegal expression", "syntax error");
    // data = data.replace("expected", "should be here, but");
    data = data.replace("Incompatible types: got", "Wrong types: you used");
    data = data.replace("Incompatible types: got", "Wrong types: you used");

    console.log(data);
  }
  console.log(`
  \n
  \n
  \n`);
  //   console.log(data);
});

// let newdata = data.split("\n");
// newdata.splice(0, 3);
// data = newdata.join("\n");
// console.log(data);
