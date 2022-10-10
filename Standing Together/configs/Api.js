const base = "http://localhost:5000/api/";
const routes = {

    admin: {
        addShelter: "admin/post",
        removeShelter: (id) => `admin/del/${id}`,
        editShelter: (id) => `admin/edit/${id}`,
        getAdminShelters: "admin/getshelter",
        getAdminShelter: (id) => `admin/getshelter/${id}`,
        getAdminUsers: (id) =>`admin/getshelterusers/${id}`,
    },
    user: {
        getShelters: "user/getshelter",
        getAdminShelter: (id) => `user/getshelter/${id}`,
        userRegister: "user/register",
        userResign: "user/resign",
        userEdit: (id) => `user/edit/${id}`,
    },

    userlist: {
        addUser: "userlist/post",
    },
};

export { base, routes };
