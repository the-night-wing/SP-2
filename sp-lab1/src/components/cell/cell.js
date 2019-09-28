import React from "react";
import "./cell.css";

const Cell = ({ label, onDeleted }) => {
  return (
    <div className="cell">
      {label}
      <button
        type="button"
        className="btn btn-outline-danger btn-sm"
        onClick={onDeleted}
      >
        <i className="fa fa-trash-o" />
      </button>
    </div>
  );
};

//TODO: ADD capability to change the label of the cell using the form tag

export default Cell;
