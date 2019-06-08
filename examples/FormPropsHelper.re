let stringifyField = (fieldProps: ReactFinalFormHooks.fieldRenderProps) => {
  let inputJs = ReactFinalFormHooks.fieldInputRenderPropsToJs(fieldProps.input);
  let metaJs = ReactFinalFormHooks.fieldMetaRenderPropsToJs(fieldProps.meta);
  let fieldJs = {
    "input": inputJs,
    "meta": metaJs
  };
  let stringified = Js.Json.stringifyAny(fieldJs);

  switch(stringified) {
    | Some(string) => string
    | None => ""
  };
}

let stringifyForm = (formProps: ReactFinalFormHooks.formRenderProps) => {
  let formJs = ReactFinalFormHooks.formRenderPropsToJs(formProps);

  let stringified = Js.Json.stringifyAny(formJs);

  switch(stringified) {
    | Some(string) => string
    | None => ""
  };
}