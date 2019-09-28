import React from "react";
import Cell from "../cell";

import "./data-view.css";

export default DataView = ({ data, onDeleted }) => {
  const datas = data.map(el => (
    <Cell
      key={el.id}
      onDeleted={() => onDeleted(el.id)}
      label={el.value}
    ></Cell>
  ));

  return <div className="container">{datas}</div>;
};
