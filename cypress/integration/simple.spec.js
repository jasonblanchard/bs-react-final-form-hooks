it('Input and submit', () => {
  cy.visit('/simple');
  
  cy.get("input[name='firstName']").type('Gob');
  cy.get("input[name='lastName']").type('Bluth');
  cy.contains("submit").click();
});

it('Validates after touch', () => {
  cy.visit('/simple');
  
  cy.get('form').contains("First Name can't be empty").should('not.exist');
  cy.get('form').contains("Last Name can't be empty").should('not.exist');
  
  cy.get("input[name='firstName']").type('Gob');
  cy.get("input[name='firstName']").clear();
  cy.get("input[name='firstName']").blur();
  cy.contains("First Name can't be empty");
  
  cy.get("input[name='lastName']").type('Bluth');
  cy.get("input[name='lastName']").clear();
  cy.get("input[name='lastName']").blur();
  cy.contains("Last Name can't be empty");
  cy.contains("submit").should('be.disabled');
});