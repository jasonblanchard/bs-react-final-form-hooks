type formFields('a) = Js.t({..}) as 'a;

/* Passing through as Js.t object to preserve state referential equality */
type form('a) = {
  .
  "batch": [@bs.meth] (unit => unit),
  "blur": [@bs.meth] (unit => unit),
  "change": [@bs.meth] (unit => unit),
  "focus": [@bs.meth] (unit => unit),
  "getFieldState": string => option(string),
  "getRegisteredFields": [@bs.meth] (unit => unit),
  "getState": [@bs.meth] (unit => unit),
  "initialize": [@bs.meth] (formFields('a) => unit),
  "isValidationPaused": [@bs.meth] (unit => unit),
  "mutators": Js.t({.}),
  "pauseValidation": [@bs.meth] (unit => unit),
  "registerField": [@bs.meth] (unit => unit),
  "reset": [@bs.meth] (option(Js.t({.})) => unit),
  "resumeValidation": [@bs.meth] (unit => unit),
  "setConfig": [@bs.meth] (unit => unit),
  "submit": [@bs.meth] (unit => unit),
  "subscribe": [@bs.meth] (unit => unit),
};

type rffUseFormOptions('a) = {
  .
  "validate": option(formFields('a) => formFields('a)),
  "onSubmit": formFields('a) => unit,
};

type rffFormRenderProps('a) = {
  .
  "active": option(string),
  "dirty": bool,
  "dirtyFields": Js.Dict.t(string),
  "dirtySinceLastSubmit": bool,
  "error": option(string),
  "errors": Js.Dict.t(string),
  "form": form('a),
  "handleSubmit": ReactEvent.Form.t => unit,
  "hasSubmitErrors": bool,
  "hasValidationErrors": bool,
  "initialValues": option(Js.Dict.t(string)),
  "invalid": bool,
  "modified": Js.Dict.t(string),
  "pristine": bool,
  "submitError": option(string),
  "submitErrors": Js.Dict.t(string),
  "submitFailed": bool,
  "submitSucceeded": bool,
  "submitting": bool,
  "touched": Js.Dict.t(string),
  "valid": bool,
  "validating": bool,
  "values": Js.Dict.t(string),
  "visited": Js.Dict.t(string)
};

[@bs.module "react-final-form-hooks"]
external rffUseForm: rffUseFormOptions('a) => rffFormRenderProps('a) =
  "useForm";

[@bs.deriving jsConverter]
type formRenderProps('a) = {
  active: option(string),
  dirty: bool,
  dirtyFields: Js.Dict.t(string),
  dirtySinceLastSubmit: bool,
  error: option(string),
  errors: Js.Dict.t(string),
  form: form('a),
  handleSubmit: ReactEvent.Form.t => unit,
  hasSubmitErrors: bool,
  hasValidationErrors: bool,
  initialValues: option(Js.Dict.t(string)),
  invalid: bool,
  modified: Js.Dict.t(string),
  pristine: bool,
  submitError: option(string),
  submitErrors: Js.Dict.t(string),
  submitFailed: bool,
  submitSucceeded: bool,
  submitting: bool,
  touched: Js.Dict.t(string),
  valid: bool,
  validating: bool,
  values: Js.Dict.t(string),
  visited: Js.Dict.t(string)
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

type rffFieldMetaRenderProps = {
  .
  "active": bool,
  "data": Js.Dict.t(string),
  "dirty": bool,
  "dirtySinceLastSubmit": bool,
  "error": string,
  "initial": option(string),
  "invalid": bool,
  "length": option(int),
  "modified": bool,
  "pristine": bool,
  "submitError": option(string),
  "submitFailed": bool,
  "submitSucceeded": bool,
  "submitting": bool,
  "touched": bool,
  "valid": bool,
  "visited": bool,
};

type rffFieldRenderProps = {
  .
  "input": rffFieldInputRenderProps,
  "meta": rffFieldMetaRenderProps,
};

type rffFieldValidateFn = option(option(string) => option(string));

[@bs.module "react-final-form-hooks"]
external rffUseField:
  (string, form('a), rffFieldValidateFn) => rffFieldRenderProps =
  "useField";

[@bs.deriving jsConverter]
type fieldInputRenderProps = {
  name: string,
  value: string,
  onChange: ReactEvent.Form.t => unit,
  onBlur: ReactEvent.Focus.t => unit,
  onFocus: ReactEvent.Focus.t => unit,
};

[@bs.deriving jsConverter]
type fieldMetaRenderProps = {
  active: bool,
  data: Js.Dict.t(string),
  dirty: bool,
  dirtySinceLastSubmit: bool,
  error: string,
  initial: option(string),
  invalid: bool,
  length: option(int),
  modified: bool,
  pristine: bool,
  submitError: option(string),
  submitFailed: bool,
  submitSucceeded: bool,
  submitting: bool,
  touched: bool,
  valid: bool,
  visited: bool,
};

type fieldRenderProps = {
  input: fieldInputRenderProps,
  meta: fieldMetaRenderProps,
};

let useField = (~name, ~form, ~validate=?, ()) => {
  let renderProps = rffUseField(name, form, validate);

  {
    input: fieldInputRenderPropsFromJs(renderProps##input),
    meta: fieldMetaRenderPropsFromJs(renderProps##meta),
  };
};
