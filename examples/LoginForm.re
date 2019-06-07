[@react.component]
let make = () => {
  /* TODO: Figure out how to use a record instead of Js.Dict for `values`. */
  let onSubmit = values =>
    switch (values) {
    | None => Js.log("Invalid")
    | Some(values) =>
      let username = Js.Dict.get(values, "username");
      let password = Js.Dict.get(values, "password");
      Js.log({j|Called with username: $username password $password|j});
    };

  let {ReactFinalFormHooks.pristine, handleSubmit, form, valid} =
    ReactFinalFormHooks.useForm(
      ~onSubmit,
      ~validate=LoginFormValidations.validate,
      (),
    );

  let usernameField =
    ReactFinalFormHooks.useField(~name="username", ~form, ());
  let passwordField =
    ReactFinalFormHooks.useField(
      ~name="password",
      ~form,
      ~validate=LoginFormValidations.validatePassword,
      (),
    );

  let usernameErrorMessage =
    switch (usernameField.meta.touched, usernameField.meta.valid) {
    | (true, false) => ReasonReact.string(usernameField.meta.error)
    | (false, _) => ReasonReact.null
    | (true, true) => ReasonReact.null
    };

  let passwordErrorMessage =
    switch (passwordField.meta.touched, passwordField.meta.valid) {
    | (true, false) => ReasonReact.string(passwordField.meta.error)
    | (false, _) => ReasonReact.null
    | (true, true) => ReasonReact.null
    };

  let disabled =
    switch (pristine, valid) {
    | (true, _) => true
    | (_, false) => true
    | (false, true) => false
    };

  <form onSubmit=handleSubmit>
    <div>
      <label htmlFor={usernameField.input.name}>
        usernameErrorMessage
        <br />
        {ReasonReact.string("Username")}
      </label>
      <input
        name={usernameField.input.name}
        value={usernameField.input.value}
        onChange={usernameField.input.onChange}
        onBlur={usernameField.input.onBlur}
        onFocus={usernameField.input.onFocus}
        id={usernameField.input.name}
      />
    </div>
    <div>
      <label htmlFor={passwordField.input.name}>
        passwordErrorMessage
        <br />
        {ReasonReact.string("password")}
      </label>
      <input
        name={passwordField.input.name}
        value={passwordField.input.value}
        onChange={passwordField.input.onChange}
        onBlur={passwordField.input.onBlur}
        onFocus={passwordField.input.onFocus}
        id={passwordField.input.name}
        type_="password"
      />
    </div>
    <button disabled> {ReasonReact.string("login")} </button>
  </form>;
};
