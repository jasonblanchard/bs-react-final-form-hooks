[@react.component]
let make = () => {
  /* TODO: Figure out how to use a record instead of Js.Dict for `values`. */
  let onSubmit = values =>
    switch (values) {
    | None => Js.log("Invalid")
    | Some(values) =>
      let firstName = Js.Dict.get(values, "firstName");
      let lastName = Js.Dict.get(values, "lastName");
      Js.log({j|Called with first name: $firstName, last name: $lastName|j});
    };

  let {ReactFinalFormHooks.pristine, handleSubmit, form, valid} =
    ReactFinalFormHooks.useForm(
      ~onSubmit,
      ~validate=LoginFormValidations.validate,
      (),
    );

  let firstNameFieldField =
    ReactFinalFormHooks.useField(~name="firstName", ~form, ());
  let lastNameField =
    ReactFinalFormHooks.useField(
      ~name="lastName",
      ~form,
      ~validate=LoginFormValidations.validateLastName,
      (),
    );

  let firstNameFieldErrorMessage =
    switch (firstNameFieldField.meta.touched, firstNameFieldField.meta.valid) {
    | (true, false) => ReasonReact.string(firstNameFieldField.meta.error)
    | (false, _) => ReasonReact.null
    | (true, true) => ReasonReact.null
    };

  let passwordErrorMessage =
    switch (lastNameField.meta.touched, lastNameField.meta.valid) {
    | (true, false) => ReasonReact.string(lastNameField.meta.error)
    | (false, _) => ReasonReact.null
    | (true, true) => ReasonReact.null
    };

  let disabled =
    switch (pristine, valid) {
    | (false, true) => false
    | (true, _) => true
    | (_, false) => true
    };

  <form onSubmit=handleSubmit>
    <div>
      <label htmlFor={firstNameFieldField.input.name}>
        firstNameFieldErrorMessage
        <br />
        {ReasonReact.string("First Name")}
      </label>
      <input
        name={firstNameFieldField.input.name}
        value={firstNameFieldField.input.value}
        onChange={firstNameFieldField.input.onChange}
        onBlur={firstNameFieldField.input.onBlur}
        onFocus={firstNameFieldField.input.onFocus}
        id={firstNameFieldField.input.name}
      />
    </div>
    <div>
      <label htmlFor={lastNameField.input.name}>
        passwordErrorMessage
        <br />
        {ReasonReact.string("Last Name")}
      </label>
      <input
        name={lastNameField.input.name}
        value={lastNameField.input.value}
        onChange={lastNameField.input.onChange}
        onBlur={lastNameField.input.onBlur}
        onFocus={lastNameField.input.onFocus}
        id={lastNameField.input.name}
      />
    </div>
    <button disabled> {ReasonReact.string("submit")} </button>
  </form>;
};
