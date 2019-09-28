import React from "react";

const FilterForm = ({ onSpecimenChange, onBinary, onSearch, onLinear }) => {
  return (
    <form className="item-add-form filter" onSubmit={e => e.preventDefault()}>
      <input
        type="text"
        onChange={onSpecimenChange}
        placeholder={"Enter search key"}
      />
      <button
        className="btn btn-outline-secondary"
        title="Binary Search"
        onClick={onBinary}
      >
        Binary Search
      </button>
      <button
        className="btn btn-outline-secondary"
        title="Search For Matches"
        onClick={onSearch}
      >
        Search For Matches
      </button>
      <button
        className="btn btn-outline-secondary"
        title="Linear Search"
        onClick={onLinear}
      >
        Linear Search
      </button>
    </form>
  );
};

export default FilterForm;
