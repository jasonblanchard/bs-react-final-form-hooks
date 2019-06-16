/* TODO: Figure out how to use a record instead of a Js.Dict for this `fields`. */
let validate = fields => {
  let results = Js.Dict.empty();

  switch (Js.Dict.get(fields, "firstName")) {
  | None
  | Some("") => Js.Dict.set(results, "firstName", "First Name can't be empty")
  | Some(_) => ()
  };

  results;
};

let validateFirstName = firstName =>
  switch (firstName) {
  | None
  | Some("") => Some("First name can't be empty")
  | Some(_) => None
  };

let validateLastName = lastName =>
  switch (lastName) {
  | None
  | Some("") => Some("Last Name can't be empty")
  | Some(_) => None
  };
