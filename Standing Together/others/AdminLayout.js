import React, { useEffect } from "react";
import AdminMenu from "./AdminMenu";
import { useAuth0 } from "@auth0/auth0-react";
import { useNavigate } from "react-router-dom";
import { authSettings } from "../configs/AuthSettings";
const AdminLayout = ({ children }) => {

  const { user } = useAuth0();
  const navigate = useNavigate();

  useEffect(() => {
    if (user && user[authSettings.rolesKey] && user[authSettings.rolesKey].length === 0) {
      navigate("/");
    }
  }, [user]);


  return (
    <div>
      <AdminMenu />
      <div className="normal-page">
        {children}
      </div>
    </div>
  );
};

export default AdminLayout;
