[@react.component]
let make = () => {
  // TODO: Figure out how to use a record instead of Js.Dict for `values`.
  let onSubmit = (values) => {
    switch(values) {
      | None => Js.log("Invalid")
      | Some(values) => {
        let username = Js.Dict.get(values, "username");
        let password = Js.Dict.get(values, "password");
        Js.log({j|Called with username: $username password $password|j});
      }
    }
  };

  let { Forms.pristine, handleSubmit, form, valid } = Forms.useForm(~onSubmit=onSubmit, ~validate=LoginFormValidations.validate, ());

  let username = Forms.useField(~name="username", ~form=form, ());
  let password = Forms.useField(~name="password", ~form=form, ~validate=LoginFormValidations.validatePassword, ());

  let usernameErrorMessage =
    switch (username.meta.touched, username.meta.valid) {
    | (true, false) => ReasonReact.string("Need to supply username")
    | (false, _) => ReasonReact.null
    | (true, true) => ReasonReact.null
  };

  let passwordErrorMessage =
    switch (password.meta.touched, password.meta.valid) {
    | (true, false) => ReasonReact.string("Need to supply password")
    | (false, _) => ReasonReact.null
    | (true, true) => ReasonReact.null
  };

  let disabled = switch(pristine, valid) {
    | (true, _) => true
    | (_, false) => true
    | (false, true) => false
  };

  <form onSubmit={handleSubmit}>
    <div>
      <label htmlFor={username.input.name}>
        {usernameErrorMessage}
        <br />
        {ReasonReact.string("Username")}
      </label>
      <input
        name={username.input.name}
        value={username.input.value}
        onChange={username.input.onChange}
        onBlur={username.input.onBlur}
        onFocus={username.input.onFocus}
        id={username.input.name}
      />
    </div>
    <div>
      <label htmlFor={password.input.name}>
        {passwordErrorMessage}
        <br />
        {ReasonReact.string("password")}
      </label>
      <input
        name={password.input.name}
        value={password.input.value}
        onChange={password.input.onChange}
        onBlur={password.input.onBlur}
        onFocus={password.input.onFocus}
        id={password.input.name}
        type_="password"
      />
    </div>
    <button disabled={disabled}>{ReasonReact.string("login")}</button>
  </form>
};