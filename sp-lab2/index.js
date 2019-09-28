class GraphNode {
  constructor(id, dlm = 1, cfr = 1, ltr = 1) {
    this.id = id;
    this.dlm = dlm;
    this.cfr = cfr;
    this.ltr = ltr;
    console.log(`${dlm} ${cfr} ${ltr}`);
  }
  passOnSignal(signal) {
    if (signal === "dlm") {
      return this.dlm;
    } else if (signal === "cfr") {
      return this.cfr;
    } else if (signal === "ltr") {
      return this.ltr;
    } else return 0;
  }
  //TODO dlm cfr ltr
}
