// TODO: Figure out how to use a record instead of a Js.Dict for this `fields`.
let validate = (fields) => {
  let results = Js.Dict.empty();

  switch (Js.Dict.get(fields, "username")) {
    | None | Some("") => Js.Dict.set(results, "username", "Can't be empty")
    | Some(_) => ()
  };

  results;
};

let validatePassword = (password) => {
  switch (password) {
      | None | Some("") => Some("Password Can't be empty")
      | Some(_) => None;
  };
};