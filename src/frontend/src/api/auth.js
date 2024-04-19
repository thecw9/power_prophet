import axios from "@/utils/csustRequest";

export function login(username, password) {
  const data =
    "grant_type=password&username=" +
    username +
    "&password=" +
    password +
    "&scope=&client_id=&client_secret=";

  return axios.post("/auth-service/access_token", data, {
    headers: {
      Accept: "application/json",
      "Content-Type": "application/x-www-form-urlencoded",
    },
  });
}

export function getUserList(page, size) {
  const data = {
    page: page,
    size: size,
  };
  return axios.post("/auth-service/user/list", data);
}

export function searchUser(keyword, page, size_per_page) {
  const params = {
    sub_str: keyword,
    page: page,
    size: size_per_page,
  };
  return axios.post("/auth-service/user/search", params);
}

export function deleteUser(id) {
  return axios.post("/auth-service/user/delete/" + id);
}

export function addUser(data) {
  return axios.post("/auth-service/user/add", data, {
    headers: {
      Accept: "application/json",
      "Content-Type": "application/json",
    },
  });
}

export function updateUser(data) {
  return axios.post("/auth-service/user/update", data, {
    headers: {
      Accept: "application/json",
      "Content-Type": "application/json",
    },
  });
}
