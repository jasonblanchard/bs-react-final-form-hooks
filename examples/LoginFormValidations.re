type formData = {
  .
  "firstName": option(string),
  "lastName": option(string)
};

let validate = values: formData => {
  let firstNameError: option(string) = switch (values##firstName) {
  | None
  | Some("") => Some("First Name can't be empty")
  | Some(_) => None
  };

  let results = {
    "firstName": firstNameError,
    "lastName": None
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
