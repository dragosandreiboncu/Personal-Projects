import React, { useEffect} from "react";
import { BrowserRouter, Route, Routes } from "react-router-dom";
import UserShelters from "../pages/User/Shelters";
import UserShelter from "../pages/User/Shelter";
import Profile from "../pages/User/Profile";
import AdminShelters from "../pages/Admin/Shelters.js";
import AdminShelter from "../pages/Admin/Shelter";
import { useAuth0 } from "@auth0/auth0-react";


const Router = () => {
  const { isAuthenticated, loginWithRedirect } = useAuth0();

  useEffect(() => {
    if (!isAuthenticated) {
      loginWithRedirect();
    }
  }, [isAuthenticated, loginWithRedirect]);
 
  return (
    isAuthenticated && (
      <BrowserRouter>
        <Routes>
          <Route exact path="/" element={<UserShelters />} />
          <Route exact path="/shelter:id" element={<UserShelter />} />
          <Route exact path="/profile" element={<Profile />} />
          <Route exact path="/admin" element={<AdminShelters />} />
          <Route exact path="/admin/shelter:id" element={<AdminShelter />} />
        </Routes>
      </BrowserRouter>
    )
  );
};

export default Router;