export default class DataBase {
  _array = [];
  _struct = [];
  _matches = [];
  _queue = 0;

  generateId = () => {
    return `f${(~~(Math.random() * 1e8)).toString(16)}`;
  };

  getElement = index => {
    if (this._array[index]) return this._array[index];
    else console.log("There's no such element");
  };

  setElement = (index, value) => {
    this._array[index] = value;
  };

  generateElement = value => {
    return {
      id: this.generateId(),
      value
    };
  };

  generateStruct = () => {
    this._struct = this._array.map(value => this.generateElement(value));
    console.log(this._struct);
  };

  deleteElement = id => {
    const index = this._struct.findIndex(el => el.id === id);
    console.log(index);
    this._struct.splice(index, 1);
    // console.log(this._struct);
  };

  addElement = value => {
    this._array.push(value);
    this._array = this._array.sort();
    this.generateStruct();
  };

  get struct() {
    return this._struct;
  }

  // get element() {
  //   return this._array;
  // }

  setArray = array => {
    this._array = array.sort();
    this.resetLastMatches();
    this._queue = 0;
    this.generateStruct();
  };

  get array() {
    const array = this._struct.map(el => el.value);
    return this._array;
  }

  showArray = () => {
    console.log(this._array);
  };

  showLastMatches = () => {
    console.log(this._matches);
  };

  showLastMatch = () => {
    const maxMatches = Math.max(...this._matches);
    const resultsAmount = this._matches.filter(el => el === maxMatches).length;

    if (maxMatches === 0) {
      console.log("No matches");
      return -1;
    }

    if (this._queue > resultsAmount) this._queue = 1;

    const cycle = resultsAmount === 1 ? 1 : this._queue;

    let result = "";
    let shift = 0;

    for (let i = 0; i < cycle; i++) {
      result = this._matches.indexOf(maxMatches, shift);
      shift = result + 1;
    }
    console.log(`${result} result`);

    console.log(`${this._array[result]}`);

    return `${this._array[result]} (${this._matches[result]} matches)`;
  };

  resetLastMatches = () => {
    this._matches = new Array(this._array.length).fill(0);
  };

  findLetterMatches = specimenLetter => {
    this._array.forEach((word, index) => {
      word.split("").forEach(letter => {
        if (letter === specimenLetter) this._matches[index]++;
      });
    });
  };

  // console.log( binarySearch(["forever", "her", 'mer', "peasd", "tomorrow", "tonight", 'yellow', "zark"], "yellow") );

  findMatches = specimen => {
    this.resetLastMatches();
    specimen.split("").forEach(specimenLetter => {
      this.findLetterMatches(specimenLetter);
    });
    if (this._queue === this.array.length) this._queue = 0;
    else this._queue++;
  };

  binarySearch = value => {
    // initial values for start, middle and end
    let start = 0;
    let stop = this._array.length - 1;
    let middle = Math.floor((start + stop) / 2);

    // While the middle is not what we're looking for and the list does not have a single item
    while (this._array[middle] !== value && start < stop) {
      if (value < this._array[middle]) {
        stop = middle - 1;
      } else {
        start = middle + 1;
      }

      // recalculate middle on every iteration
      middle = Math.floor((start + stop) / 2);
    }

    // if the current middle item is what we're looking for return it's index, else return -1
    return this._array[middle] !== value ? -1 : middle;
  };

  linearSearch = specimen => {
    let result = -1;
    this._array.forEach((word, index) => {
      // console.log(word === specimen);
      if (word === specimen) result = index;
    });
    return result;
  };
}
