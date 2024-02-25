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
  const query_params = {
    keyword: keyword,
    page: page,
    size_per_page: size_per_page,
  };
  return axios.get("v1/sys-service/users/search", {
    params: query_params,
  });
}

export function deleteUser(id) {
  return axios.post("/auth-service/user/delete/" + id);
}
