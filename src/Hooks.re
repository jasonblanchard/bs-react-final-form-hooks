/* Passing through as Js.t object to preserve state referential identity */
type form = Js.t({
  .
  batch: [@bs.meth] unit => unit,
  blur: [@bs.meth] unit => unit,
  change: [@bs.meth] unit => unit,
  focus: [@bs.meth] unit => unit,
  getFieldState: string => option(string),
  getRegisteredFields: [@bs.meth] unit => unit,
  getState: [@bs.meth] unit => unit,
  initialize: [@bs.meth] unit => unit,
  isValidationPaused: [@bs.meth] unit => unit,
  mutators: Js.t({.}),
  pauseValidation: [@bs.meth] unit => unit,
  registerField: [@bs.meth] unit => unit,
  reset: [@bs.meth] option(Js.t({.})) => unit,
  resumeValidation: [@bs.meth] unit => unit,
  setConfig: [@bs.meth] unit => unit,
  submit: [@bs.meth] unit => unit,
  subscribe: [@bs.meth] unit => unit
});

type rffUseFormOptions = {
  .
  "validate": option(Js.Dict.t(string) => Js.Dict.t(string)),
  "onSubmit": option(Js.Dict.t(string)) => unit,
};

/* TODO: Add all form render props */
type rffFormRenderProps = {
  .
  "pristine": bool,
  "handleSubmit": ReactEvent.Form.t => unit,
  "submitting": bool,
  "form": form,
  "valid": bool,
};

[@bs.module "react-final-form-hooks"]
external rffUseForm: rffUseFormOptions => rffFormRenderProps = "useForm";

/* TODO: Add all form render props */
[@bs.deriving jsConverter]
type formRenderProps = {
  pristine: bool,
  handleSubmit: ReactEvent.Form.t => unit,
  submitting: bool,
  form: form,
  valid: bool,
};

let useForm = (~onSubmit, ~validate=?, ()) => {
  let options = {"onSubmit": onSubmit, "validate": validate};

  let renderProps = rffUseForm(options);

  formRenderPropsFromJs(renderProps);
};

type rffFieldInputRenderProps = {
  .
  "name": string,
  "value": string,
  "onChange": ReactEvent.Form.t => unit,
  "onBlur": ReactEvent.Focus.t => unit,
  "onFocus": ReactEvent.Focus.t => unit,
};

/* TODO: Add all field meta props */
type rffFieldMetaRenderProps = {
  .
  "touched": bool,
  "valid": bool,
  "error": string
};

type rffFieldRenderProps = {
  .
  "input": rffFieldInputRenderProps,
  "meta": rffFieldMetaRenderProps,
};

type rffFieldValidateFn = option(option(string) => option(string));

[@bs.module "react-final-form-hooks"]
external rffUseField:
  (string, form, rffFieldValidateFn) => rffFieldRenderProps =
  "useField";


[@bs.deriving jsConverter]
type fieldInputRenderProps = {
  name: string,
  value: string,
  onChange: ReactEvent.Form.t => unit,
  onBlur: ReactEvent.Focus.t => unit,
  onFocus: ReactEvent.Focus.t => unit,
};

/* TODO: Add all field meta props */
[@bs.deriving jsConverter]
type fieldMetaRenderProps = {
  touched: bool,
  valid: bool,
  error: string
};

type fieldRenderProps = {
  input: fieldInputRenderProps,
  meta: fieldMetaRenderProps,
};

let useField = (~name, ~form, ~validate=?, ()) => {
  let renderProps = rffUseField(name, form, validate);
  /* Js.log(renderProps); */

  {
    input: fieldInputRenderPropsFromJs(renderProps##input),
    meta: fieldMetaRenderPropsFromJs(renderProps##meta),
  };
};
