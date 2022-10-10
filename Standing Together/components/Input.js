import React, { forwardRef } from "react";

const Input = forwardRef((props, ref) => {
  const { label, icon, ...rest } = props;
  return (
    <label>
      {label && <span>{label}</span>}
      {icon}
      <input className={`input`} {...rest} ref={ref} />
    </label>
  );
});

export default Input;
