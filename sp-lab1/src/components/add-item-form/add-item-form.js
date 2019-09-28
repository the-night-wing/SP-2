import React from "react";
import "./add-item-form.css";

const AddItemForm = ({ onLabelChange, onSubmit }) => {
  return (
    <form className="item-add-form adding" onSubmit={onSubmit}>
      <input
        type="text"
        onChange={onLabelChange}
        placeholder={"Enter Name of The Item"}
      />
      <button className="btn btn-outline-secondary" title="Add Item">
        Add Item
      </button>
    </form>
  );
};

export default AddItemForm;
