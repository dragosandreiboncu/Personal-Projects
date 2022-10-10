import "./App.css";
import React from "react";
import Router from "./others/Routing";
import "./styling/global.tailwind.css";
import Wrapper from "./others/AuthWrapper";


const App = () => {
  return (
    <Wrapper>
      <Router/>
    </Wrapper>
  );
};

export default App;
