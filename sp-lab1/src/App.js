import React, { Component } from "react";
import "./App.css";
import "./bootstrap.css";
import DataView from "./components/data-view";
import FilterForm from "./components/filter-form";
import AddItemForm from "./components/add-item-form";
import DataBase from "./data-base.js";

export default class App extends Component {
  dataStruct = new DataBase();

  componentDidMount() {
    this.setState({
      array: this.dataStruct.array
    });
  }

  onSpecimenChange = e => {
    this.setState({
      specimen: e.target.value
    });
  };

  onArrayValueChange = e => {
    let txt = e.target.value;
    let array = txt.split(", ");
    console.log(array);
    this.setState({
      arrayValue: txt,
      array
    });
  };

  onItemAdd = e => {
    e.preventDefault();
    this.dataStruct.addElement(this.state.newElement);
    this.forceUpdate();
  };

  onNewElementChange = e => {
    this.setState({
      newElement: e.target.value
    });
  };

  startSearch = e => {
    const { specimen } = this.state;
    e.preventDefault();
    this.dataStruct.findMatches(specimen);
    this.dataStruct.showLastMatches();
    const searchResult = this.dataStruct.showLastMatch();
    this.setState({
      searchResult: !(searchResult + 1) ? "No Matches" : searchResult
    });
  };

  binarySearch = e => {
    e.preventDefault();
    const { specimen } = this.state;
    const searchResult = this.dataStruct.binarySearch(specimen);
    this.setState({
      searchResult: !(searchResult + 1) ? "No Matches" : searchResult
    });
  };

  linearSearch = e => {
    e.preventDefault();
    const { specimen } = this.state;
    const searchResult = this.dataStruct.linearSearch(specimen);
    this.setState({
      searchResult: !(searchResult + 1) ? "No Matches" : searchResult
    });
  };

  setData = e => {
    e.preventDefault();
    const { array, arrayValue } = this.state;
    array.length === 0
      ? this.dataStruct.setArray(arrayValue.split(", "))
      : this.dataStruct.setArray(array);

    this.dataStruct.showArray();
    this.forceUpdate();
  };

  state = {
    newElement: "",
    specimen: "",
    array: this.dataStruct.array,
    arrayValue:
      "Mary, Elsa, Viky, Gordon, Charlie, Leo, Grace, Jeremy, Freddie, Harry",
    searchResult: "Start a search"
  };

  render() {
    const { arrayValue, searchResult } = this.state;
    // const dataStruct = new DataBase();
    // dataStruct.findMatches("Jeremy");
    // dataStruct.showLastMatches();

    return (
      <div className="App">
        <form className="item-add-form" onSubmit={this.setData}>
          <input
            type="text"
            onChange={this.onArrayValueChange}
            value={arrayValue}
            placeholder="Enter array"
          />
          <button className="btn btn-outline-secondary" onClick={this.setData}>
            Set Array
          </button>
        </form>

        <DataView
          data={this.dataStruct.struct}
          onDeleted={id => {
            this.dataStruct.deleteElement(id);
            this.forceUpdate();
          }}
        />
        <FilterForm
          onSpecimenChange={this.onSpecimenChange}
          onBinary={this.binarySearch}
          onLinear={this.linearSearch}
          onSearch={this.startSearch}
        />
        <AddItemForm
          onSubmit={this.onItemAdd}
          onLabelChange={this.onNewElementChange}
        />
        <p>{`Search Result : ${searchResult}`}</p>
      </div>
    );
  }
}
