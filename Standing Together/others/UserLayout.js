import React, { useEffect } from "react";
import UserMenu from "./UserMenu";
import { useAuth0 } from "@auth0/auth0-react";
import { useNavigate } from "react-router-dom";
import { authSettings } from "../configs/AuthSettings";


const UserLayout = ({ children }) => {
  const { user } = useAuth0();
  const navigate = useNavigate();
  
  useEffect(() => {
    if (user && user[authSettings.rolesKey] && user[authSettings.rolesKey].length === 1) {
      navigate("/admin");
    }
  }, [user]);

  return (
    <div className="layout">
      <UserMenu />
      <div className="normal-page">
        {children}
      </div>
    </div>
  );
};

export default UserLayout;
